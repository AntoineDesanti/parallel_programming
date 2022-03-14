#ifndef RADIXSORT_H_INCLUDED
#define RADIXSORT_H_INCLUDED

struct tablo
{
	int *tab;
	int size;
};

void printArray(struct tablo *tmp);
int *descente(struct tablo *input);
void final(struct tablo *a, struct tablo *b);
int *genTabWithRandoms(int n);
int *genTabFromFile(char *filename, int array_size);
int randomNumber(int lower, int upper);
bool isNumber(char number[]);


#endif