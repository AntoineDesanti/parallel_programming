from numba import cuda
import numpy as np
import numba as nb
import math
from PIL import Image as img
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--tx", type=int, default=16)
parser.add_argument("--ty", type=int, default=8)
parser.add_argument("--gsize", type=int, default=7)
parser.add_argument("--gsigma", type=int, default=100)
parser.add_argument("input_file")
parser.add_argument("output_file")
args = parser.parse_args()
print(args)

gaussia_kernel = np.array([[1,4,6,4,1],[4,16,24,16,4],[6,24,36,24,6],[4,16,24,16,4],[1,4,6,4,1]],int)

@cuda.jit
def blur_kernel(input,output,kernel): 
    
    x, y = cuda.grid(2)
    # final_value = np.zeros([ 0, 0, 0])

    if x < input.shape[0] and y < input.shape[1]:
        kernel_size = kernel.shape[0]

        r = np.uint8(0)
        g = np.uint8(0)
        b = np.uint8(0)

        top_left_x = x-2
        top_left_y = y-2

        for row in range(0,kernel_size):
            for column in range(0,kernel_size):
                r += input[top_left_x+row][top_left_y+column][0] * gaussia_kernel[row][column]
                g += input[top_left_x+row][top_left_y+column][1] * gaussia_kernel[row][column]
                b += input[top_left_x+row][top_left_y+column][2] * gaussia_kernel[row][column]

        r = r // 256
        g = g //256
        b = b //256

        output[x,y,0] = r
        output[x,y,1] = g
        output[x,y,2] = b

im = img.open("tigre_low.jpg")
im_array = np.array(im)
im_array = np.ascontiguousarray(im_array.transpose(1,0,2))

if args.gsize or args.gsigma:
    #test
    print()
    
cuda_im_array = cuda.to_device(im_array)
cuda_array_output = cuda.device_array(im_array.shape,dtype = np.uint8)

x_dim = math.ceil(im_array.shape[0]/16) #replace 16 per tx value
y_dim = math.ceil(im_array.shape[1]/8) #replace 16 per ty value
blur_kernel[(x_dim,y_dim,1),(16,8,3)](cuda_im_array,cuda_array_output, cuda.to_device(gaussia_kernel))

#Result
im_arrayResult = cuda_array_output.copy_to_host()
im = img.fromarray(im_arrayResult.transpose((1, 0,2)))
im.save(args.output_file)