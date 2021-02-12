#include "convert.h"


void convert(char *rfile, char *wfile){
    /*On va lire le fichier donné en argument dans le dossier test et écrire dans le fichier donné en argument se trouvant dans hexified
    Nous devons donc donner le chemin (relatif ici) des dossiers tests/ et hexified/ par rapport à l'executable de notre programme */ 
    char path1[] = "./tests/";
    char path2[] = "./hexified/";

/*On utilise strcat avec le path du dossier d'ouverture et le nom du fichier pour créer le chemin relatif du fichier à ouvrir
strcat va concatener ces deux chaines de caractères */

    FILE *read = fopen(strcat(path1,rfile),"r");

//On vérifie premièrement si le fichier de lecture existe pour ne pas créer un autre fichier inutilement dans hexified/ 

    if(read == NULL){
        perror("Le fichier de lecture n'existe pas ou ne se trouve pas dans tests/\n");
        exit(EXIT_FAILURE);
    }
    FILE *write = fopen(strcat(path2,wfile),"w");
    if (write == NULL){
        perror("Erreur lors de la création ou de l'ouverture du fichier d'écriture");
        exit(EXIT_FAILURE);
    }
    
//On créer des tableaux de chaines de caracètres pour chaque type d'instructions
    char *instructionsJ[]= {"J","JAL"};
    char *instructionsR[] = {"ADD","SUB","MULT","DIV","AND","OR","XOR","ROTR","SLL","SRL","SLT","MFHI","MFLO","JR","NOP"};
    char *instructionsI[] = {"ADDI","SW","LW","LUI","BEQ","BNE","BGTZ","BLEZ"};
    
    char c;
    while (fread(&c,1,1,read)){  //ici fread lit un bloc de un octet du fichier read et le place dans c, cette fonction renvoie le nombre de bloc lu, donc si elle renvoie 0, c'est qu'on est à la fin du fichier
//On traite le cas ou l'on a un commentaire, et donc on continue de parcourir le fichier jusqu'à arriver à la fin de la ligne commenté ou bien la fin du fichier		
        if(c == '#'){
            while(c!='\n' && !feof(read)){
                fread(&c,1,1,read);
            }
        }
//Maintenant, si notre ligne n'est ni un commentaire, ni une ligne vide, on lit les premiers caracteres jusqu'à obtenir un espace : ce qui correspond à l'instruction
        else if (c != '\n'){
            char op_code[5];
            int i =0;
            while(c!=' '&& c != '\n' && !feof(read)){
                op_code[i] = c;
                fread(&c,1,1,read);				
                i++;
            }
            op_code[i]='\0';
/*Après avoir placé l'instruction lu dans une chaine de caractere, on la compare aux différentes chaines de caractere present dans nos tableaux d'instructions, 
on a donc une disjonction de cas pour pouvoir convertir chaque ligne d'instruction en hexadécimal. On utilisera fscanf dans nos différents cas, car cette fonction
nous permet de récupérer les bonnes valeurs au bon endroit sans avoir à utiliser de boucle : on peut récupérer les valeurs de tous les registres et les valeurs
immédiates avec une seule instruction*/
            //ADD
            if (strcmp(op_code,instructionsR[0]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int rd;
                fscanf(read,"$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_add;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //SUB
            else if (strcmp(op_code,instructionsR[1]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int rd;
                fscanf(read,"$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_sub;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //MULT
            else if (strcmp(op_code,instructionsR[2]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                fscanf(read,"$%d,$%d",&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                code+= rs;
                code+=rt;
                code+=op_mult;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //DIV
            else if (strcmp(op_code,instructionsR[3]) == 0){ 
                int code = 0x00000000;
                int rs;
                int rt;
                fscanf(read,"$%d,$%d",&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                code+= rs;
                code+=rt;
                code+=op_div;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //AND
            else if (strcmp(op_code,instructionsR[4]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int rd;
                fscanf(read,"$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_and;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //OR
            else if (strcmp(op_code,instructionsR[5]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int rd;
                fscanf(read,"$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_or;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //xOR
            else if (strcmp(op_code,instructionsR[6]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int rd;
                fscanf(read,"$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_xor;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //ROTR
            else if (strcmp(op_code,instructionsR[7]) == 0){
                int code = 0x00000000;
                int rt;
                int rd;
                int sa;
                fscanf(read,"$%d,$%d,%d",&rd,&rt,&sa);
                rt = rt << 16;
                rd = rd << 11;
                sa = sa << 6;
                code+= 1 << 21;
                code+=sa;
                code+=rt;
                code+=rd;
                code+=op_srl;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //SLL
            else if (strcmp(op_code,instructionsR[8]) == 0){
                int code = 0x00000000;
                int rt;
                int rd;
                int sa;
                fscanf(read,"$%d,$%d,%d",&rd,&rt,&sa);
                rt = rt << 16;
                rd = rd << 11;
                sa = sa << 6;
                code+=sa;
                code+=rt;
                code+=rd;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //SRL
            else if (strcmp(op_code,instructionsR[9]) == 0){
                int code = 0x00000000;
                int rt;
                int rd;
                int sa;
                fscanf(read,"$%d,$%d,%d",&rd,&rt,&sa);
                rt = rt << 16;
                rd = rd << 11;
                sa = sa << 6;
                code+=sa;
                code+=rt;
                code+=rd;
                code+=op_srl;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //SLT
            else if (strcmp(op_code,instructionsR[10]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int rd;
                fscanf(read,"$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_slt;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //MFHI
            else if (strcmp(op_code,instructionsR[11]) == 0){
                int code = 0x00000000;
                int rd;
                fscanf(read,"$%d",&rd);
                rd = rd << 11;
                code+=rd;
                code+=op_mfhi;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //MFLO
            else if (strcmp(op_code,instructionsR[12]) == 0){
                int code = 0x00000000;
                int rd;
                fscanf(read,"$%d",&rd);
                rd = rd << 11;
                code+=rd;
                code+=op_mflo;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //JR
            else if (strcmp(op_code,instructionsR[13]) == 0){
                int code = 0x00000000;
                int rs;
                fscanf(read,"$%d",&rs);
                rs = rs << 21;
                code+= rs;
                code+=op_jr;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //NOP
            else if (strcmp(op_code,instructionsR[14]) == 0){
                int code = 0x00000000;
                //fscanf(read,"%c",&c);
	            fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                    fscanf(read,"%c",&c);
                }
            }
            //ADDI
            else if (strcmp(op_code,instructionsI[0]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int im;
                fscanf(read,"$%d,$%d,%d",&rt,&rs,&im);
                code += op_addi << 26;
                code += rs << 21;
                code += rt << 16;
                code += im;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //SW
            else if (strcmp(op_code,instructionsI[1]) == 0){
                int code = 0x00000000;
                int base;
                int rt;
                int offset;
                fscanf(read,"$%d,%d($%d)",&rt,&offset,&base);
                code += op_sw << 26;
                code += base << 21;
                code += rt << 16;
                code += offset;
                fprintf(write,"%.8x\n",code);   
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }      
            }
            //LW
            else if (strcmp(op_code,instructionsI[2]) == 0){
                int code = 0x00000000;
                int base;
                int rt;
                int offset;
                fscanf(read,"$%d,%d($%d)",&rt,&offset,&base);
                code += op_lw << 26;
                code += base << 21;
                code += rt << 16;
                code += offset;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //LUI
            else if (strcmp(op_code,instructionsI[3]) == 0){
                int code = 0x00000000;
                int rt;
                int im;
                fscanf(read,"$%d,%d",&rt,&im);
                code += op_lui << 26;
                code += rt << 16;
                code += im;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //BEQ
            else if (strcmp(op_code,instructionsI[4]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int offset;
                fscanf(read,"$%d,$%d,%d",&rs,&rt,&offset);
                code += op_beq << 26;
                code += rs << 21;
                code += rt << 16;
                code += offset;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //BNE
            else if (strcmp(op_code,instructionsI[5]) == 0){
                int code = 0x00000000;
                int rs;
                int rt;
                int offset;
                fscanf(read,"$%d,$%d,%d",&rs,&rt,&offset);
                code += op_bne << 26;
                code += rs << 21;
                code += rt << 16;
                code += offset;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //BGTZ
            else if (strcmp(op_code,instructionsI[6]) == 0){
                int code = 0x00000000;
                int rs;
                int offset;
                fscanf(read,"$%d,%d",&rs,&offset);
                code += op_bgtz << 26;
                code += rs << 21;
                code += offset;
                fprintf(write,"%.8x\n",code);
                 if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //BLEZ
            else if (strcmp(op_code,instructionsI[7]) == 0){
                int code = 0x00000000;
                int rs;
                int offset;
                fscanf(read,"$%d,%d",&rs,&offset);
                code += op_blez << 26;
                code += rs << 21;
                code += offset;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //J
            else if (strcmp(op_code,instructionsJ[0]) == 0){
                int code = 0x00000000;
                int target;
                fscanf(read,"%d",&target);
                code+=op_j << 26;
                code+=target;
                fprintf(write,"%.8x\n",code);
                 if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
            //JAL
            else if (strcmp(op_code,instructionsJ[1]) == 0){
                int code = 0x00000000;
                int target;
                fscanf(read,"%d",&target);
                code+=op_jal << 26;
                code+=target;
                fprintf(write,"%.8x\n",code);
                if (!feof(read)){
                        fscanf(read,"%c",&c);
                    }
            }
        }
    }
    fclose(read);
    fclose(write);           
}

/*Cette fonction nous permet de faire une disjonction de cas en fonction de l'instruction lu dans le main. On utilisera scanf dans nos différents cas, car cette fonction
nous permet de récupérer les bonnes valeurs au bon endroit sans avoir à utiliser de boucle : on peut récupérer les valeurs de tous les registres et les valeurs immédiates 
avec une seule instruction.

La fonction retourne la valeur en héxadécimal de l'instruction tapé au clavier*/

int convert_interactive(char* op_code){
    char *instructionsJ[]= {"J","JAL"};
    char *instructionsR[] = {"ADD","SUB","MULT","DIV","AND","OR","XOR","ROTR","SLL","SRL","SLT","MFHI","MFLO","JR","NOP"};
    char *instructionsI[] = {"ADDI","SW","LW","LUI","BEQ","BNE","BGTZ","BLEZ"};
    
    int code = 0x00000000;
            //ADD
            if (strcmp(op_code,instructionsR[0]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                int rd;
                scanf("$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_add;
            }
            //SUB
            else if (strcmp(op_code,instructionsR[1]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                int rd;
                scanf("$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_sub;
            }
            //MULT
            else if (strcmp(op_code,instructionsR[2]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                scanf("$%d,$%d",&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                code+= rs;
                code+=rt;
                code+=op_mult;
            }
            //DIV
            else if (strcmp(op_code,instructionsR[3]) == 0){ 
                code = 0x00000000;
                int rs;
                int rt;
                scanf("$%d,$%d",&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                code+= rs;
                code+=rt;
                code+=op_div;
            }
            //AND
            else if (strcmp(op_code,instructionsR[4]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                int rd;
                scanf("$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_and;
            }
            //OR
            else if (strcmp(op_code,instructionsR[5]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                int rd;
                scanf("$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_or;
            }
            //xOR
            else if (strcmp(op_code,instructionsR[6]) == 0){
            code = 0x00000000;
            int rs;
            int rt;
            int rd;
            scanf("$%d,$%d,$%d",&rd,&rs,&rt);
            rs = rs << 21;
            rt = rt << 16;
            rd = rd << 11;
            code+= rs;
            code+=rt;
            code+=rd;
            code+=op_xor;
            }
            //ROTR
            else if (strcmp(op_code,instructionsR[7]) == 0){
                code = 0x00000000;
                int rt;
                int rd;
                int sa;
                scanf("$%d,$%d,%d",&rd,&rt,&sa);
                rt = rt << 16;
                rd = rd << 11;
                sa = sa << 6;
                code+= 1 << 21;
                code+=sa;
                code+=rt;
                code+=rd;
                code+=op_srl;
            }
            //SLL
            else if (strcmp(op_code,instructionsR[8]) == 0){
            code = 0x00000000;
            int rt;
            int rd;
            int sa;
            scanf("$%d,$%d,%d",&rd,&rt,&sa);
            rt = rt << 16;
            rd = rd << 11;
            sa = sa << 6;
            code+=sa;
            code+=rt;
            code+=rd;
            }
            //SRL
            else if (strcmp(op_code,instructionsR[9]) == 0){
                code = 0x00000000;
                int rt;
                int rd;
                int sa;
                scanf("$%d,$%d,%d",&rd,&rt,&sa);
                rt = rt << 16;
                rd = rd << 11;
                sa = sa << 6;
                code+=sa;
                code+=rt;
                code+=rd;
                code+=op_srl;
            }
            //SLT
            else if (strcmp(op_code,instructionsR[10]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                int rd;
                scanf("$%d,$%d,$%d",&rd,&rs,&rt);
                rs = rs << 21;
                rt = rt << 16;
                rd = rd << 11;
                code+= rs;
                code+=rt;
                code+=rd;
                code+=op_slt;
            }
            //MFHI
            else if (strcmp(op_code,instructionsR[11]) == 0){
                code = 0x00000000;
                int rd;
                scanf("$%d",&rd);
                rd = rd << 11;
                code+=rd;
                code+=op_mfhi;                
            }
            //MFLO
            else if (strcmp(op_code,instructionsR[12]) == 0){
                code = 0x00000000;
                int rd;
                scanf("$%d",&rd);
                rd = rd << 11;
                code+=rd;
                code+=op_mflo;
            }
            //JR
            else if (strcmp(op_code,instructionsR[13]) == 0){
                code = 0x00000000;
                int rs;
                scanf("$%d",&rs);
                rs = rs << 21;
                code+= rs;
                code+=op_jr;
            }
            //NOP
            else if (strcmp(op_code,instructionsR[14]) == 0){
                code = 0x00000000;
                //fscanf(read,"%c",&c);
            }
            //ADDI
            else if (strcmp(op_code,instructionsI[0]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                int im;
                scanf("$%d,$%d,%d",&rt,&rs,&im);
                code += op_addi << 26;
                code += rs << 21;
                code += rt << 16;
                code += im;
            }
            //SW
            else if (strcmp(op_code,instructionsI[1]) == 0){
                code = 0x00000000;
                int base;
                int rt;
                int offset;
                scanf("$%d,%d($%d)",&rt,&offset,&base);
                code += op_sw << 26;
                code += base << 21;
                code += rt << 16;
                code += offset;     
            }
            //LW
            else if (strcmp(op_code,instructionsI[2]) == 0){
                code = 0x00000000;
                int base;
                int rt;
                int offset;
                scanf("$%d,%d($%d)",&rt,&offset,&base);
                code += op_lw << 26;
                code += base << 21;
                code += rt << 16;
                code += offset;
            }
            //LUI
            else if (strcmp(op_code,instructionsI[3]) == 0){
                code = 0x00000000;
                int rt;
                int im;
                scanf("$%d,%d",&rt,&im);
                code += op_lui << 26;
                code += rt << 16;
                code += im;
            }
            //BEQ
            else if (strcmp(op_code,instructionsI[4]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                int offset;
                scanf("$%d,$%d,%d",&rs,&rt,&offset);
                code += op_beq << 26;
                code += rs << 21;
                code += rt << 16;
                code += offset;
            }
            //BNE
            else if (strcmp(op_code,instructionsI[5]) == 0){
                code = 0x00000000;
                int rs;
                int rt;
                int offset;
                scanf("$%d,$%d,%d",&rs,&rt,&offset);
                code += op_bne << 26;
                code += rs << 21;
                code += rt << 16;
                code += offset;
            }
            //BGTZ
            else if (strcmp(op_code,instructionsI[6]) == 0){
                code = 0x00000000;
                int rs;
                int offset;
                scanf("$%d,%d",&rs,&offset);
                code += op_bgtz << 26;
                code += rs << 21;
                code += offset;
            }
            //BLEZ
            else if (strcmp(op_code,instructionsI[7]) == 0){
                code = 0x00000000;
                int rs;
                int offset;
                scanf("$%d,%d",&rs,&offset);
                code += op_blez << 26;
                code += rs << 21;
                code += offset;
            }
            //J
            else if (strcmp(op_code,instructionsJ[0]) == 0){
                code = 0x00000000;
                int target;
                scanf("%d",&target);
                code+=op_j << 26;
                code+=target;
            }
            //JAL
            else if (strcmp(op_code,instructionsJ[1]) == 0){
                code = 0x00000000;
                int target;
                scanf("%d",&target);
                code+=op_jal << 26;
                code+=target;
            }
    return code;         
}
