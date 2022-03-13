#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

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

//Montée
int* generateTreeFromTab(int input[], int size){
  struct tablo *tmp = malloc(sizeof(struct tablo));
  tmp->size = size * 2;
  tmp->tab = malloc(tmp->size * sizeof(int));

	for(int i =  size * 2; i > size -1; i--){	
		tmp->tab[i] = input[i-size];
	}

	int j = size * 2 - 1;
	#pragma omp parallel for
	for(int i =  size-1; i > 0; i--){	
		tmp->tab[i] = tmp->tab[j] + tmp->tab[j-1];
		j-=2;
	}

	return tmp;
} 

int* descente(struct tablo *input){
	struct tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size =  input->size;
	tmp->tab = malloc(input->size * sizeof(int));
	
	  
	for(int i = 0; i < input->size -1; i++){	
		tmp->tab[i] = 0;
	}

	for(int i = 1; i <= (int)log2(input->size / 2); i++){	
		int index = pow(2, i);
		int index2 = pow(2, i + 1) -1;
		#pragma omp parallel for
		for(int j = index; j <= index2; j++){
			if(j % 2 == 0){
				//fils gauche
				tmp->tab[j] = tmp->tab[j/2];
			}
			else{
				//fils droit
				tmp->tab[j] = tmp->tab[j/2] + input->tab[j-1];
			}
		}
	}
	return tmp;
}

void final(struct tablo *a, struct tablo *b) {
    for (int i = 1; i <= a->size; i++) {
        b->tab[i] = b->tab[i] + a->tab[i];
    }
}

int main(int argc, char **argv) {
	int input_tab[] = { 2,4,5,8};	
	struct tablo *tree_tab  = generateTreeFromTab(input_tab, 4);
	printArray(tree_tab);
	struct tablo *tree_tab_descente = descente(tree_tab);
	printArray(tree_tab);
	final(tree_tab,tree_tab_descente);
	printArray(tree_tab_descente);

	


}

