#include "affichage.h"

void afficherRegistres(int registre[32], int *HI, int *LO){
    printf("Register states\n");
    for(int i = 0;i<32;i++){
       if(i%4 == 0){
           printf("\n");
       }
       printf("$%.2d: %d\t",i,registre[i]);
    }
    printf("\n");
    printf("HI: %d\nLO: %d\n\n",*HI,*LO);
    

}

void afficherMemoire(memoire *m){   //on affiche que les adresses utilisés
    if (*m == NULL){
        printf("Memoire vide\n");
    }
    else{
        memoire i = *m;
        int cnt = 0;
        printf("Memory\n");
        while((i != NULL)){
            if (cnt%3 == 0) printf("\n");
            printf("0x%.8x: %d\t", i->adresse, i->valeur);
            i = i->suivant;
            cnt++;
        }
    }
    printf("\n\n");
}