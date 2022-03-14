#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

struct tablo
{
	int *tab;
	int size;
};

void printArray(struct tablo *tmp)
{
	printf("---- Array of size %i ---- \n", tmp->size);
	int size = tmp->size;
	int i;
	for (i = 0; i < size; ++i)
	{
		printf("%i ", tmp->tab[i]);
	}
	printf("\n");
}

int *descente(struct tablo *input)
{
}

void final(struct tablo *a, struct tablo *b)
{
}

int *genTabWithRandoms(int n)
{
	struct tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size = n;
	tmp->tab = malloc(n * sizeof(int));
	for (int i = 0; i < tmp->size; i++)
	{
		tmp->tab[i] = randomNumber(0, 1024);
	}
	return tmp;
}

// Based on https://cboard.cprogramming.com/c-programming/137188-obtain-space-separated-values-text-file.html
int *genTabFromFile(char *filename, int array_size)
{
	char entire_row1[7];
    int value;
    int  i=0, r;

	struct tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size = array_size;
	tmp->tab = malloc(array_size * sizeof(int));

 
    FILE *fp;
    fp = fopen(filename, "rt");

    if (fp == NULL) 
	{ 
        printf("File does not exist"); 
        exit(1); 
	}
 
    while ((r = fscanf(fp, "%d", &value)) != EOF) {
        tmp->tab[i] = value;
		i++;
	}
  
    fclose(fp);


	return tmp;
}

int randomNumber(int lower, int upper)
{
	int num = (rand() %
			   (upper - lower + 1)) +
			  lower;
	return num;
}

bool isNumber(char number[])
{
	int i = 0;

	// checking for negative numbers
	if (number[0] == '-')
		i = 1;
	for (; number[i] != 0; i++)
	{
		// if (number[i] > '9' || number[i] < '0')
		if (!isdigit(number[i]))
			return false;
	}
	return true;
}

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

	struct tablo *tab;
	if (inputFileUsed)
	{
		tab = genTabFromFile(input_file_name, array_size);
	}
	else
	{
		tab = genTabWithRandoms(array_size);
	}

	printArray(tab);
}
