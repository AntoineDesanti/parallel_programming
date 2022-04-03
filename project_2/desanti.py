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
parser.add_argument("--gsigma", type=int, default=15)
parser.add_argument("input_file")
parser.add_argument("output_file")
args = parser.parse_args()
print(args)

gaussia_kernel = np.array([[1,4,6,4,1],[4,16,24,16,4],[6,24,36,24,6],[4,16,24,16,4],[1,4,6,4,1]],int)

@cuda.jit
def blur_kernel(input,output,kernel): 
    x, y = cuda.grid(2)
    if x < input.shape[0] and y < input.shape[1]:
        r = 0
        g = 0
        b = 0

        k_offset = kernel.shape[0] // 2
        
        for col in range(-k_offset, k_offset + 1):
            for row in range(-k_offset, k_offset + 1):
                pixel_x = x + col
                pixel_y = y + row
                if pixel_x < 0 or pixel_x >= input.shape[0] or pixel_y < 0 or pixel_y >= input.shape[1]:
                    u, v = x, y
                r += input[pixel_x, pixel_y, 0] * kernel[col + k_offset, row + k_offset]
                g += input[pixel_x, pixel_y, 1] * kernel[col + k_offset, row + k_offset]
                b += input[pixel_x, pixel_y, 2] * kernel[col + k_offset, row + k_offset]
        output[x, y, 0] = r
        output[x, y, 1] = g
        output[x, y, 2] = b



def compute_kernel():
    center=(int)(args.gsize/2)
    kernel=np.zeros((args.gsize,args.gsize))
    for i in range(args.gsize):
       for j in range(args.gsize):
          diff=np.sqrt((i-center)**2+(j-center)**2)
          kernel[i,j]=np.exp(-(diff**2)/(2*args.gsigma**2))
    return kernel/np.sum(kernel)

# if not args.gsize
#    custom_kernel = gaussia_kernel

custom_kernel = compute_kernel()
# print(custom_kernel)
im = img.open(args.input_file)
im_array = np.array(im)
im_array = np.ascontiguousarray(im_array.transpose(1,0,2))


cuda_im_array = cuda.to_device(im_array)
cuda_array_output = cuda.device_array(im_array.shape,dtype = np.uint8)

x_dim = math.ceil(im_array.shape[0]/args.tx) #replace 16 per tx value
y_dim = math.ceil(im_array.shape[1]/args.ty) #replace 16 per ty value
blur_kernel[(x_dim,y_dim,1),(16,8,3)](cuda_im_array,cuda_array_output, cuda.to_device(custom_kernel))

#Result
im_arrayResult = cuda_array_output.copy_to_host()
im = img.fromarray(im_arrayResult.transpose((1, 0,2)))
im.save(args.output_file)