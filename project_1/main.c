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
		}
		// printf("input file used: %s output_file_name:%s number_of_threads:%d",
		// input_file_name,output_file_name,number_of_threads  );
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

	tablo *tab;

	if (inputFileUsed)
	{
		tab = genTabFromFile(input_file_name, array_size);
	}
	else
	{
		tab = genTabWithRandoms(array_size);
	}

	 printArray(tab);
	 radix_sort(&tab,n_value);
	 printArray(tab);

//	tablo* prefix_tab= malloc(sizeof(struct tablo));
//	prefix_tab->size = 4;
//	prefix_tab->tab = malloc(prefix_tab->size * sizeof(int));
//
//	prefix_tab->tab[0] = 2;
//	prefix_tab->tab[1] = 5;
//	prefix_tab->tab[2] = 8;
//	prefix_tab->tab[3] = 1;
//
//
//    tablo *pref_tab = prefix(prefix_tab);
//    printArray(pref_tab);
//
//

    free(tab);
}
