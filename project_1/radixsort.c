#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h> 

struct tablo {
    int * tab;
    int size;
};

void printArray(struct tablo *tmp) {
    printf("---- Array of size %i ---- \n", tmp->size);
    int size = tmp->size;
    int i;
    for (i = 0; i < size; ++i) {
        printf("%i ", tmp->tab[i]);
    }
    printf("\n");
}

int* descente(struct tablo *input){

}

void final(struct tablo *a, struct tablo *b) {

}

int* randomFilledTab(int n){
	return;
}

int main(int argc, char **argv) {
	if(argc < 3){
		printf("Needs the following arguments: <value of N> <size of the array> [<input file name>] <output file name> [number of threads, otherwise the by default number]");
	}
	bool inputFileUsed = false;

	if(argv[3]){
		inputFileUsed = true;
	}

	int n_value = argv[1];
	int array_size = argv[2];
	char* input_file_name = argv[3];
	char* output_file_name = argv[4];
	int number_of_threads = 4;

	if(argv[5]){
		number_of_threads = argv[5];
	}

	struct tablo *tab;
	if(inputFileUsed){

	}
	else{
		tab = randomFilledTab(4);
	}
	 


}

