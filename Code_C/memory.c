#include "memory.h"


/*on vient retourner la valeur qui se trouve à l'adresse ad dans la liste chainée qui nous serre de mémoire*/
int lw(int ad, memoire *m){
    memoire suiv = *m;
    int result = 0;
    while(suiv != NULL && suiv->adresse!=ad){
        suiv = suiv->suivant;
    }
    if (suiv != NULL) 
        result = suiv->valeur;;
    return result;
}


/*on vient store en mémoire, si c'est une adresse encore jamais utilisée on vient créer un nouvel élément dans la liste chainée tout en la gardant triée
par ordre croissant par rapport aux adresses*/
void sw(int ad, int x, memoire *m,int *taille_mem){ 
    memoire suiv = *m;
    memoire prec = NULL;

    while(suiv != NULL && suiv->adresse < ad){   //on se place à l'endroit où insérer notre nouvel élément
        prec = suiv; 
        suiv = suiv->suivant;
    }
    if (suiv != NULL && suiv->adresse == ad){  //si on a deja quelque chose en memoire a cette adresse la
        suiv->valeur = x;
    }
    else if (*taille_mem <= TAILLE_MAX){
        *taille_mem +=1;
        memoire elem = malloc(sizeof(case_mem));
        elem->valeur = x;
        elem->adresse = ad;
        elem->suivant = suiv;
        if(prec == NULL){      //si on a une insertion en tête ou non
            *m = elem;
        }

        else{
            prec->suivant = elem;
        }
    }
}


/*cette fonction supprime la liste chainée*/
void vider_memoire(memoire *m){
	memoire suiv = *m;
	memoire supp = NULL;
	
	while(suiv != NULL){
		supp = suiv;
		suiv=suiv->suivant;
		free(supp);
	}
	*m = NULL;
}