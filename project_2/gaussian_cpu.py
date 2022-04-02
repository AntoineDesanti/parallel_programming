from numba import cuda
import numba as nb
import numpy as np
from PIL import Image as img

gaussia_kernel = np.array([[1,4,6,4,1],[4,16,24,16,4],[6,24,36,24,6],[4,16,24,16,4],[1,4,6,4,1]],int)

def compute_pixel(x,y,input_array): 
    top_left_x = x-2
    top_left_y = y-2
    final_value = np.array([ 0, 0, 0])

    for row in range(0,5):
        for column in range(0,5):
            for dim in range(0,3):
                # print(top_left_x+row,top_left_y+column )
                final_value[dim] +=input_array[top_left_x+row][top_left_y+column][dim] * gaussia_kernel[row][column]
    for dim in range(0,3):
        final_value[dim] = final_value[dim] // 256

    #print(final_value)
    return final_value


if __name__ == '__main__':
    image = img.open("tigre.jpg" )
    print(image.size)

    img_array: np.ndarray = np.array(image)
    #img_array = np.ascontiguousarray(img_array.transpose(1,0,2)) # we rotate the array

    new_img_array = np.copy(img_array)
    # new_image = new_image.convert('L')
 
    for row in range(0, img_array.shape[0]):
        for pixel in range(0, img_array.shape[1]): #for each pixels of the output picture
            if row >= 2 and pixel >= 2 and row <= img_array.shape[0] -4 and pixel <= img_array.shape[1] -4: 
               # print(row,  img_array.shape[0])
                new_img_array[row,pixel] = compute_pixel(row,pixel,img_array)

    new_image = img.fromarray(new_img_array)
    new_image.save("blurred.jpg")

#    img_array = np.dot(img_array[...,:3], [0.2989,0.5870,0.8])
   # print(img_array.shape)

    # new_image = img.fromarray(img_array)
    # new_image = new_image.convert('L')
    # print(new_image.size)

    # new_image.save("TIGER.png")