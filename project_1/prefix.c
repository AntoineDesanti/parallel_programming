#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include<stdbool.h>

typedef struct tablo {
    int * tab;
    int size;
}tablo;


typedef struct tablo tablo;

static void printArray(tablo *tmp)
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
//Montée
static struct tablo* montee(struct tablo* tab){
  struct tablo *tmp = malloc(sizeof(struct tablo));
  tmp->size = tab->size * 2;
  tmp->tab = malloc(tmp->size * sizeof(int));

	#pragma omp parallel for
    for (int i = 0; i <  tab->size; i++) {
        tmp->tab[i +  tab->size] = tab->tab[i];
    }

    for (int i = (int) log2( tab->size) - 1; i >= 0; i--) {
        int index = pow(2, i);
        int index2 = pow(2, i + 1) - 1;
	#pragma omp parallel for
        for (int j = index; j <= index2; j++) {
            tmp->tab[j] = tmp->tab[2 * j] + tmp->tab[2 * j + 1];
        }
    }
	return tmp;
}

static struct tablo* descente(struct tablo *input){
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

void final(struct tablo *tree_tab_descente, struct tablo *tree_tab) {
	 #pragma omp parallel for
	for(int i = 0; i < tree_tab_descente->size; i++)
    {
        tree_tab_descente->tab[i] = tree_tab_descente->tab[i] + tree_tab->tab[i];
    }
}

struct tablo * prefix(struct tablo *a){

	struct tablo *tab_montee = montee(a);
    struct tablo *tab_descente = descente(tab_montee);
	final(tab_descente,tab_montee);

    struct tablo *tmp = malloc(sizeof(struct tablo));
    tmp->size = tab_descente->size / 2;
    tmp->tab = malloc(tmp->size * sizeof(int));
    for (int i = 0; i < tmp->size; i++)
    {
        tmp->tab[i] = tab_descente->tab[i + tmp->size];
    }

	return tmp;
}

bool isPowerOfTwo(int n)
{
    if(n==0)
        return false;

    return (ceil(log2(n)) == floor(log2(n)));
}


struct tablo *subset(struct tablo *tab, int start, int end){
    struct tablo *sub = malloc(sizeof(struct tablo));
    sub->size = end - start + 1;
    sub->tab = malloc(sub->size * sizeof(int));
    for(int i = 0; i < sub->size; i++){
        sub->tab[i] = tab->tab[start + i];
    }
    return sub;
}

//merge tablo
struct tablo *merge(struct tablo *tab1, struct tablo *tab2){
    struct tablo *merged = malloc(sizeof(struct tablo));
    merged->size = tab1->size + tab2->size;
    merged->tab = malloc(merged->size * sizeof(int));
    int i = 0, j = 0, k = 0;

    while(i < tab1->size){
        merged->tab[k] = tab1->tab[i];
        i++;
        k++;
    }
    while(j < tab2->size){
        merged->tab[k] = tab2->tab[j];
        j++;
        k++;
    }
    return merged;
}
struct tablo * prefix_parallel(struct tablo *a){
    struct tablo *result = malloc(sizeof(struct tablo));
  
    int k[10];
    int array_indice = 0;
    int k_indice = 0;

    if(isPowerOfTwo(a->size)){
        return prefix(a);
    }

    for(int i = (int) log2(a->size)+1; i >= 0; i--){
      int current_pow = pow(2,i);
      if(current_pow < a->size && (array_indice+current_pow-1) <a->size){
          //printf("current_pow %i\n", current_pow);
          struct tablo *tmp_tablo = prefix(subset(a,array_indice,array_indice + current_pow - 1));
          k[k_indice] = tmp_tablo->tab[tmp_tablo->size - 1];

          if(k_indice > 0){
              for(int l=1; l<k_indice+1; l++){
                  for(int j = 0; j < tmp_tablo->size; j++){
                      tmp_tablo->tab[j] = tmp_tablo->tab[j] + k[l - 1];
                  }
              }
              result = merge(result,tmp_tablo);
          }
          else{
              result = tmp_tablo;
          }
          k_indice++;
          array_indice+= current_pow;
      }
    }
    return result;
}



static void free_tablo(tablo *t)
{
    free(t->tab);
    free(t);
}