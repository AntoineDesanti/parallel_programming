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

bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

int main(int argc, char **argv) {
	if(argc < 4){
		printf("Needs the following arguments: <value of N> <size of the array> [<input file name>] <output file name> [number of threads, otherwise the by default number]");
	}
	//BEGIN PARAMS SETUP
	bool inputFileUsed = true;
	int n_value = argv[1];
	int array_size = argv[2];
	char* input_file_name; 
	char* output_file_name;
	int number_of_threads = 4;

	if(!isNumber(argv[3]) && isNumber(argv[4])){
		inputFileUsed = false;
	}

	if(inputFileUsed){
		input_file_name = argv[3];
		output_file_name = argv[4];
		if(argv[5]){
			number_of_threads = atoi(argv[5]);
		}
		// printf("input file used: %s output_file_name:%s number_of_threads:%d",
		// input_file_name,output_file_name,number_of_threads  );
	}
	else{
		output_file_name = argv[3];
			if(argv[4]){
			number_of_threads = atoi(argv[4]);
		}
		//printf("NO input file. output_file_name:%s number_of_threads:%d",output_file_name,number_of_threads  );
	}
	//END PARAMS SETUP


	struct tablo *tab;
	if(inputFileUsed){

	}
	else{
		tab = randomFilledTab(4);
	}
	 


}

