#ifndef RADIXSORT_H_INCLUDED
#define RADIXSORT_H_INCLUDED


void printArray(struct tablo *tmp);
struct tablo *permute(struct tablo *tab_a,struct tablo *index);
int* bit(int i, struct tablo *tab_a);
struct tablo *not(struct tablo *tab);
struct tablo *size_suffix(struct tablo *tab);
struct tablo *suffix_old(struct tablo *tab);
void final(struct tablo *a, struct tablo *b);
int *genTabWithRandoms(int n);
int *genTabFromFile(char *filename, int array_size);
int randomNumber(int lower, int upper);
bool isNumber(char number[]);
long tobinary(int dno);
int countDigitsToWriteValue(int value);
bool bit_status(int val, int position);
int* split(struct tablo *tab_a,struct tablo *flags);
int* scan(struct tablo *array);
struct tablo *index_rs(struct tablo *bit,struct tablo *ldown, struct tablo *lup);
struct tablo *scan_old(struct tablo *tab);
int *radix_sort(struct tablo **input_tab, int N);
#endif