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

long tobinary(int dno){
	//https://www.tutorialspoint.com/decimal-to-binary-conversion-using-c-programming
   long bno=0,rem,f=1;
   while(dno != 0){
      rem = dno % 2;
      bno = bno + rem * f;
      f = f * 10;
      dno = dno / 2;
   }
   return bno;;
}

int countDigitsToWriteValue(int value){
	return log_2(value) + 1;
}

int log_2(int val){
	return log(val)/log(2);
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


