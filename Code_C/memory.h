#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 1e9

typedef struct case_mem case_mem;
struct case_mem {
int adresse;
int valeur ; 
case_mem* suivant ;
};

typedef case_mem *memoire;

int lw(int ad, memoire *m);
void sw(int ad, int x, memoire *m,int *taille_mem);

void vider_memoire(memoire *m);