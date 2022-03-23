#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


typedef struct tablo {
    int * tab;
    int size;
}tablo;

typedef struct tablo tablo;

struct tablo * prefix(struct tablo *a);
struct tablo* montee(struct tablo* tab);
struct tablo* descente(struct tablo* input);