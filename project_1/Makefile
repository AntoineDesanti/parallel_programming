# main: quicksort.c
# 	gcc-11  quicksort.c -o main -lm -fopenmp -Wall

# parallel_quicksort: parallel_quicksort.c
# 	gcc-11  parallel_quicksort.c -o parallel_quicksort -lm -fopenmp -Wall

# prefix: prefix.c
# 	gcc-11  prefix.c -o prefix -lm -fopenmp -Wall

radixsort: main.c
	gcc-11 -g main.c radixsort.c prefix.c suffix.c -o ./output/radixsort -lm -fopenmp -Wall
	