#ifndef RADIXSORT_H_INCLUDED
#define RADIXSORT_H_INCLUDED


void printArray(struct tablo *tmp);
int *descente(struct tablo *input);
int* permute(struct tablo *tab_a,struct tablo *index);
int* bit(int i, struct tablo *tab_a);
void final(struct tablo *a, struct tablo *b);
int *genTabWithRandoms(int n);
int *genTabFromFile(char *filename, int array_size);
int randomNumber(int lower, int upper);
bool isNumber(char number[]);
long tobinary(int dno);
int countDigitsToWriteValue(int value);
bool bit_status(int val, int position);

#endif