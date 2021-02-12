#include "affichage.h"

/*(mode interactif)cette fonction nous permet de vider le buffer avant de demander une autre ligne à l'utilisateur */

void vider_buffer(void){
    int i;
    do{
        i=getchar();
    }while(i!='\n'  && i!=EOF);
}


/*(mode interactif)cette fonction nous permet de savoir si ce qu'à commencer à écrire l'utilisateur est bien une instruction valide (= une instruction que l'on a implémenté)
elle retourne 1 si c'est le cas et 0 sinon*/
int dinguerie(char *mot){
    char *instructions[]= {"ADD","SUB","MULT","DIV","AND","OR","XOR","ROTR","SLL","SRL","SLT","MFHI","MFLO","JR","NOP","ADDI","SW","LW","LUI","BEQ","BNE","BGTZ","BLEZ"};
    int i=0;
    int result = 0;
    while(i<23){
        if(strcmp(mot,instructions[i]) == 0)
            result = 1;
        i++;
    }
    return result;
}

int main(int argc, char *argv[]){
/*mode non-interactif + pas à pas*/    
    if(argc == 2 || argc == 3){
		
        convert(argv[1],argv[1]);  //on vient créer le fichier du code en hexa du fichier test passé en parametre
		
        char path[] = "./hexified/";
        FILE *hexfile = fopen(strcat(path,argv[1]),"r");  //on vient lire le fichier hexa
        if(hexfile == NULL){
            perror("Le fichier de lecture n'existe pas ou ne se trouve pas dans tests/\n");
            exit(EXIT_FAILURE);
        }
		/*initialisation des registres*/
        int REGISTRE[32];
        for(int i=0;i<32;i++)REGISTRE[i]=0;
        REGISTRE[29] = 0x40000000; //On initialise SP à l'adresse 0x40000000
		
        int HI=0,LO=0,PC = 0;  //initialisation des registres spéciaux
        
		int taille_mem = 0;  //permet d'être sur de ne pas dépasser les 4Go de mémoires (on l'utilise dans le module memory)
        
		int ligne;  //contiendra la valeur d'une ligne d'instructon
		
		/*initialisation des memoires*/
        memoire mem = NULL;
        memoire mem_inst = NULL;
       
		int instruction;
        int adresse_inst = 0;  //indice qui nous servira à savoir ou l'on écrit dans la mémoire (des instructions) et à quel moment on a éxécuté toutes les instructions (= on a fini le programme)
        while (!feof(hexfile)){            //on écrit les instructions en mémoire (la partie de la mémoire qui leur est réservé)
			fscanf(hexfile,"%x\n",&instruction);
            sw(adresse_inst, instruction, &mem_inst,&taille_mem);
			adresse_inst+=4;
        }
        fclose(hexfile);
		
		
		while (PC < adresse_inst){  //on vient exécuter le programme
			ligne = lw(PC, &mem_inst);
			Decode(ligne,REGISTRE,&HI,&LO,&PC,&mem,&taille_mem);
            PC+=4;
            REGISTRE[0] = 0;
            if(argc ==3 && strcmp(argv[2],"-pas") == 0){  //cas ou l'instruction est pas à pas
                printf("Instruction en cours: %.8x\n",ligne);
                afficherRegistres(REGISTRE,&HI,&LO);
                afficherMemoire(&mem);
                getchar(); //pour demander d'appyuer sur entrée
            }
		}
        if(argc != 3 ){ //on affiche à la fin de l'exécution du programme les registres et la mémoire
			afficherRegistres(REGISTRE,&HI,&LO);
			afficherMemoire(&mem);
		}
		
		
		/*on vide la memoire*/
        vider_memoire(&mem);
        vider_memoire(&mem_inst);
        return 0;
    }
	
	
/*mode interactif*/	
    else if( argc == 1){ 
		/*initialisation des registres*/
        int REGISTRE[32];
        for(int i=0;i<32;i++)REGISTRE[i]=0;
        REGISTRE[29] = 0x40000000; //On initialise SP à l'adresse 0x40000000
        
		int HI=0,LO=0,PC = 0; //initialisation des registres spéciaux
		
        int taille_mem = 0;   //permet d'être sur de ne pas dépasser les 4Go de mémoires (on l'utilise dans le module memory)
		
        int ligne;  //contiendra la valeur d'une ligne d'instructon
		
		
        memoire mem = NULL;  //initialisation de la memoire
		
        printf("Mode intéractif: Entrez une par une vos commandes\n");
        printf("Voir registres: 'RE'\nVoir mémorie 'ME'\nVoir mémoire et registres 'RM'\nQuitter 'EXIT'\n");
		
		/*on vient dans un premier temps lire le début de la ligne entrée par l'utilisateur afin de voir si il demande l'affiche de la mémoire et/ou des
		registres et sinon de voir si son instruction est valide*/
		
        char debut[5]; //plus long mot d'instruction sur 4 lettres, donc tableau de 5 pour avoir \0
        do{
            scanf("%s",debut);
            if(debut[0] !='#'){  //si ce n'est pas un commentaire
                if(dinguerie(debut)){  //l'utilsateur entre une instruction
                    getchar();  //on vient lire se qui suit l'espace (' ') apres le nom de l'instruction si l'instruction est valide 
                    ligne = convert_interactive(debut);
                    printf("%.8x\n",ligne);
                    Decode(ligne,REGISTRE,&HI,&LO,&PC,&mem,&taille_mem);
                    PC+=4;
					REGISTRE[0] = 0;
                }
                else if (strcmp(debut,"RE") == 0){  //l'utilisateur a demandé à voir les registres
                    afficherRegistres(REGISTRE,&HI,&LO);
                }
                else if (strcmp(debut,"ME") == 0){  //l'utilisateur a demandé à voir la memoire
                    afficherMemoire(&mem);
                }
                else if (strcmp(debut,"RM") == 0){  //l'utilisateur a demandé à voir la memoire et les registres
                    afficherRegistres(REGISTRE,&HI,&LO);
                    afficherMemoire(&mem);
                }
                else if(strcmp(debut,"EXIT") != 0){  //l'utilisateur a écrit quelque chose d'invalide
                    printf("Veuillez entrer une instruction correcte MERCI !\n");
                }
            }
            vider_buffer();  //on vide le buffer avant de prendre une nouvelle ligne afin de ne pas avoir d'élément "parasite" venant de la ligne précédente sur la nouvelle ligne
        }while(strcmp(debut,"EXIT") != 0);  //tant que l'utilisateur n'entre pas EXIT
        printf("Au revoir !\n");
        vider_memoire(&mem);   //on vide la memoire
        return 0;

    }
	else{
        printf("Mauvaise utilisation de la commande\n");
        return 0;
    }
}
