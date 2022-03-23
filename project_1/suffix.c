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
typedef struct tablo tablo;

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
struct tablo* generateTreeFromTab_s(int input[], int size){
  struct tablo *tmp = malloc(sizeof(struct tablo));
  tmp->size = size * 2;
  tmp->tab = malloc(tmp->size * sizeof(int));

	//#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        tmp->tab[i + size] = input[i];
    }

    for (int i = (int) log2(size) - 1; i >= 0; i--) {
        int index = pow(2, i);
        int index2 = pow(2, i + 1) - 1;
	//#pragma omp parallel for
        for (int j = index; j <= index2; j++) {
            tmp->tab[j] = tmp->tab[2 * j] + tmp->tab[2 * j + 1];
        }
    }
	return tmp;
}

struct tablo* descente(struct tablo *input){
	struct tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size =  input->size;
	tmp->tab = malloc(input->size * sizeof(int));


	for(int i = 0; i < input->size -1; i++){
		tmp->tab[i] = 0;
	}
	// #pragma omp parallel for
	for(int i = 1; i <= (int)log2(input->size / 2); i++){
		int index = pow(2, i);
		int index2 = pow(2, i + 1) -1;

		int val_pere;
		//the following was suppose to work
// #pragma omp parallel for
		for(int j = index; j <= index2; j++){

			if(j % 2 == 0){
				//fils gauche
				val_pere = tmp->tab[j/2];
				tmp->tab[j] = val_pere + input->tab[j+1];
			}
			else{
				//fils droit
				tmp->tab[j] = val_pere;
			}
		}
	}
	return tmp;
}

struct tablo *final(struct tablo *a, struct tablo *b) {
    for (int i = 1; i <= a->size; i++) {
        b->tab[i] = b->tab[i] + a->tab[i];
    }
	return b;
}

struct tablo * suffix(struct tablo *a){
	struct tablo *tmp = malloc(sizeof(struct tablo));
	tmp->size =  a->size;
	tmp->tab = malloc(a->size * sizeof(int));

	tmp = descente(a);
	tmp = final(a,tmp);

	return tmp;
}

void free_tablo(tablo *t)
{
    free(t->tab);
    free(t);
}

// int main(int argc, char **argv) {
// 	int input_tab[] = { 2, 5, 8, 1};
// 	struct tablo *tree_tab  = generateTreeFromTab_s(input_tab, 4);
// 	printArray(tree_tab);

// 	struct tablo *tree_tab_descente = descente(tree_tab);
// 	printArray(tree_tab_descente);
//     for(u_int8_t i = 0; i < 8; i++)
//     {
//         tree_tab_descente->tab[i] = tree_tab_descente->tab[i] + tree_tab->tab[i];
//     }
//     printArray(tree_tab_descente);
//     free_tablo(tree_tab);
//     free_tablo(tree_tab_descente);
// }