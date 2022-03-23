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

//Montée
struct tablo* montee(struct tablo* tab){
  struct tablo *tmp = malloc(sizeof(struct tablo));
  tmp->size = tab->size * 2;
  tmp->tab = malloc(tmp->size * sizeof(int));

	//#pragma omp parallel for
    for (int i = 0; i <  tab->size; i++) {
        tmp->tab[i +  tab->size] = tab->tab[i];
    }

    for (int i = (int) log2( tab->size) - 1; i >= 0; i--) {
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

void final(struct tablo *tree_tab_descente, struct tablo *tree_tab) {
	for(u_int8_t i = 0; i < 8; i++)
    {
        tree_tab_descente->tab[i] = tree_tab_descente->tab[i] + tree_tab->tab[i];
    }
}

struct tablo * prefix(struct tablo *a){

	struct tablo *tab_montee = montee(a);
    struct tablo *tab_descente = descente(tab_montee);
	final(tab_descente,tab_montee);
	//printf("%d",tmp->tab[1]);
	return tab_descente;
}

void free_tablo(tablo *t)
{
    free(t->tab);
    free(t);
}