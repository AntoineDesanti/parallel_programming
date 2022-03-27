#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include "radixsort.h"
#include "prefix.h"

#define SEC_TO_US(sec) ((sec)*1000000)
#define NS_TO_US(ns)    ((ns)/1000)
// macros from https://stackoverflow.com/questions/5833094/get-a-timestamp-in-c-in-microseconds

// ./output/radixsort 1021 10 myInput myfile 2
int main(int argc, char **argv)
{
	if (argc < 4)
	{
		printf("Needs the following arguments: <value of N> <size of the array> [<input file name>] <output file name> [number of threads, otherwise the by default number]");
	}
	// BEGIN PARAMS SETUP
	bool inputFileUsed = true;
	int n_value = atoi(argv[1]);
	int array_size = atoi(argv[2]);
	char *input_file_name;
	char *output_file_name;
	int number_of_threads = 4;

	if (!isNumber(argv[3]) && isNumber(argv[4]))
	{
		inputFileUsed = false;
	}

	if (inputFileUsed)
	{
		input_file_name = argv[3];
		output_file_name = argv[4];
		if (argv[5])
		{
			number_of_threads = atoi(argv[5]);
			printf("Number of threads: %d\n", number_of_threads);
			printf("Output file name: %s\n", output_file_name);

		}
	}
	else
	{
		output_file_name = argv[3];
		if (argv[4])
		{
			number_of_threads = atoi(argv[4]);
		}
		// printf("NO input file. output_file_name:%s number_of_threads:%d",output_file_name,number_of_threads  );
	}
	// END PARAMS SETUP

	tablo *tab_to_sort;

	if (inputFileUsed)
	{
		tab_to_sort = genTabFromFile(input_file_name, array_size);
	}
	else
	{
		tab_to_sort = genTabWithRandoms(array_size);
	}

	//we define the number of threads we are going to use
	omp_set_num_threads(number_of_threads);

	printArray(tab_to_sort);


	struct timespec start, stop;
    timespec_get(&start, TIME_UTC);
	radix_sort(&tab_to_sort,n_value);
    timespec_get(&stop, TIME_UTC);

	int64_t elapsed_time = (SEC_TO_US((int64_t)stop.tv_sec) + NS_TO_US((int64_t)stop.tv_nsec)) 
	- (SEC_TO_US((int64_t)start.tv_sec) + NS_TO_US((int64_t)start.tv_nsec));

	printf("Time_in_microsec= %lu\n", elapsed_time);
	//print elapsed time in micro seconds

	printArray(tab_to_sort);
	//write n_value, array_size, number_of_threads, elapsed_time in the file output_file_name
	FILE *fp;
	fp = fopen(output_file_name, "w");
	fprintf(fp, "N=%d Size=%d Threads=%d Time_in_microsec=%lu\n", n_value, array_size, number_of_threads, elapsed_time);
	for (int i = 0; i < array_size; i++)
	{
		fprintf(fp, "%d ", tab_to_sort->tab[i]);
	}
	fclose(fp);




	// tablo* prefix_tab= malloc(sizeof(struct tablo));
	// prefix_tab->size = 4;
	// prefix_tab->tab = malloc(prefix_tab->size * sizeof(int));

	// prefix_tab->tab[0] = 2;
	// prefix_tab->tab[1] = 4;
	// prefix_tab->tab[2] = 5;
	// prefix_tab->tab[3] = 8;

	// tablo *pref_tab3 = size_suffix(prefix_tab);
  	// printArray(pref_tab3);

    free(tab_to_sort);
	return 0;
}
