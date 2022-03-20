#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct tablo
{
	int *tab;
	int size;
} tablo;

void printArray(tablo *tmp)
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


int randomNumber(int lower, int upper)
{
	int num = (rand() %
			   (upper - lower + 1)) +
			  lower;
	return num;
}
tablo *genTabWithRandoms(int n)
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
	return log2(value) + 1;
}

bool bit_status(int val, int position){
	return (val >> position) & 1;
}

tablo *bit(int i,tablo *tab_a){
	// Given a tab, will return in an array for each value of A if the i'th bit of the value is 0 or 1
	tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size = tab_a->size;
	tmp->tab = malloc(tmp->size * sizeof(int));

	for(int j=0; j < tmp->size; j++){
		if(bit_status(tab_a->tab[j],i)){
			tmp->tab[j]=1;
		}
		else{
			tmp->tab[j]=0;
		}
	}
	return tmp;
}

struct tablo *scan(struct tablo *tab){
	struct tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size = tab->size;
	tmp->tab = malloc(tab->size * sizeof(int));

	int previous = 0;
	for(int i=0; i < tmp->size; i++){
		tmp->tab[i] = previous;
		previous += tab->tab[i];
	}
	return tmp;
}

tablo *suffix(tablo *tab){
	//size - suffix
	tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size = tab->size;
	tmp->tab = malloc(tab->size * sizeof(int));

	int result = 0;
	for(int i = tmp->size - 1; i >= 0; i--){
		if(tab->tab[i] == 1){
			tmp->tab[i] = ++result;
		}
		else{
			tmp->tab[i] = result;
		}
	}

	for(int i = 0; i < tmp->size; i++){
		 tmp->tab[i] = tab->size - tmp->tab[i];
	}

	return tmp;
}

tablo *not(tablo *tab){
	tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size = tab->size;
	tmp->tab = malloc(tab->size * sizeof(int));
	for(int i=0; i < tmp->size; i++){
		tmp->tab[i] = 1 - tab->tab[i];
	}
	return tmp;
}

 tablo *index_rs(tablo *bit, tablo *ldown, struct tablo *lup) {
    tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size = bit->size;
	tmp->tab = malloc(bit->size * sizeof(int));
    for (int i = 0; i < bit->size; ++i){
		if(bit->tab[i]){
			tmp->tab[i] = lup->tab[i];
		}
		else{
			tmp->tab[i] = ldown->tab[i];
		}
	}

    return tmp;
}

tablo *permute(tablo *tab, tablo *index) {
    tablo *permute = malloc(sizeof(tablo));
	permute->size = tab->size;
	permute->tab = malloc(tab->size * sizeof(int));
    for (int i = 0; i < permute->size; ++i){
        permute->tab[index->tab[i]] = tab->tab[i];
	}
    return permute;

}

tablo *split(tablo *tab_a,tablo *flags){
	tablo *ldown = scan(not(flags));
	tablo *lup = suffix(flags); 

	return permute(tab_a, index_rs(flags,ldown,lup));
}

void radix_sort(tablo **input_tab, int N){

	for(int i = 0; i <= (int) log2(N); ++i){
		*input_tab = split(*input_tab, bit(i, *input_tab));
	}
}

// Based on https://cboard.cprogramming.com/c-programming/137188-obtain-space-separated-values-text-file.html
tablo *genTabFromFile(char *filename, int array_size)
{
    int value;
    int  i=0, r;

	tablo *tmp = malloc(sizeof(struct tablo));
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


