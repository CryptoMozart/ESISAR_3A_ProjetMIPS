#include "register.h"

/*cette fonction décode le code hexadecimal contenu dans ligne, et exécute l'instruction en appelant pour chaque instruction sa fonction définie plus bas
qui effectue les changements nécessaires sur les différents registres ou qui appelle le module memory si il s'agit d'instruction sur la memoire*/

/*on a découpé les différentes disjonctions de cas en fonction de la ressemblence de certaines fonction (même début de code, même nom de registre...)*/

void Decode(int ligne, int REGISTRE[32], int *HI, int *LO,int *PC, memoire *m, int *taille_mem){
	if ((ligne & MASK_special) == 0){    //cas des codes d'instrcutions commencant par 000000
		int op_code = ligne & MASK_op_code;
		if ((op_code == op_add)||(op_code == op_sub)||(op_code == op_and)||(op_code == op_or)||(op_code == op_slt)||(op_code == op_xor)){
			int rs = (ligne&MASK_rs) >> 21;
			int rt = (ligne&MASK_rt) >> 16;
			int rd = (ligne&MASK_rd) >> 11;
			if(op_code == op_add)add(&REGISTRE[rs],&REGISTRE[rt],&REGISTRE[rd]);
			else if(op_code == op_and)and(&REGISTRE[rs],&REGISTRE[rt],&REGISTRE[rd]);
			else if(op_code == op_sub)sub(&REGISTRE[rs],&REGISTRE[rt],&REGISTRE[rd]);
			else if(op_code == op_or)or(&REGISTRE[rs],&REGISTRE[rt],&REGISTRE[rd]);
			else if(op_code == op_slt)slt(&REGISTRE[rs],&REGISTRE[rt],&REGISTRE[rd]);
			else if(op_code == op_xor)xor(&REGISTRE[rs],&REGISTRE[rt],&REGISTRE[rd]);
		}
		else if ((op_code == op_mult)||(op_code == op_div)){
			int rs = (ligne&MASK_rs) >> 21;
			int rt = (ligne&MASK_rt) >> 16;
			if(op_code == op_mult)mult(&REGISTRE[rs],&REGISTRE[rt],HI,LO);
			else if(op_code == op_div)Div(&REGISTRE[rs],&REGISTRE[rt],HI,LO);
		}
		else if (op_code == op_rotr){
			int rt = (ligne&MASK_rt) >> 16;
			int rd = (ligne&MASK_rd) >> 11;
			int sa = (ligne&MASK_sa) >> 6;
			int R = (ligne&MASK_R) >> 21;
			if (R == 1) rotr(&REGISTRE[rt],&REGISTRE[rd],sa);
			else srl(&REGISTRE[rt],&REGISTRE[rd],sa);
		}
		else if ((op_code == op_mflo)||(op_code == op_mfhi)){
			int rd = (ligne&MASK_rd) >> 11;
			if(op_code == op_mflo)mflo(&REGISTRE[rd],LO);
			else if(op_code == op_mfhi)mfhi(&REGISTRE[rd],HI);
		}
		else if (op_code == op_jr){
			int rs = (ligne&MASK_rs) >> 21;
			jr(&REGISTRE[rs],PC);
		}
		else if (op_code == op_sll){
			int rt = (ligne&MASK_rt) >> 16;
			int rd = (ligne&MASK_rd) >> 11;
			int sa = (ligne&MASK_sa) >> 6;
			sll(&REGISTRE[rt],&REGISTRE[rd], sa);
		}
	}
	else{    //ce qui ne commence pas par 000000
		int op_code = (ligne & MASK_special) >> 26;
		if ((op_code== op_addi)||(op_code == op_beq)||(op_code == op_bne)){
			int rs = (ligne&MASK_rs) >> 21;
			int rt = (ligne&MASK_rt) >> 16;
			short im = ligne&MASK_imm;
			if (op_code == op_addi) addi(&REGISTRE[rs],&REGISTRE[rt],im);
			else if (op_code == op_beq) beq(&REGISTRE[rs],&REGISTRE[rt],im,PC);
			else bne(&REGISTRE[rs],&REGISTRE[rt],im,PC);
		}
		else if ((op_code == op_lw)||(op_code == op_sw)){
			int base = (ligne&MASK_rs) >> 21;
			int rt = (ligne&MASK_rt) >> 16;
			short offset = ligne&MASK_imm;
			if (op_code == op_lw) decode_lw(&REGISTRE[base],&REGISTRE[rt],offset,m);
            else decode_sw(&REGISTRE[base],&REGISTRE[rt],offset,m,taille_mem);
		}
		else if ((op_code == op_bgtz)||(op_code == op_blez)){
			int rs = (ligne&MASK_rs) >> 21;
			short offset = ligne&MASK_imm;
			if (op_code == op_bgtz) bgtz(&REGISTRE[rs],offset,PC);
			else blez(&REGISTRE[rs],offset,PC);
		}
		else if (op_code == op_lui){
			int rt = (ligne&MASK_rt) >> 16;
			short offset = ligne&MASK_imm;
			lui(&REGISTRE[rt],offset);
		}
	}
}

void add(int *rs,int *rt,int *rd){
	*rd = (*rs) + (*rt);
}
void sub(int *rs,int *rt,int *rd){
	*rd = (*rs) - (*rt);
}
void and(int *rs,int *rt,int *rd){
	*rd = (*rs) & (*rt);
}
void or(int *rs,int *rt,int *rd){
	*rd = (*rs) | (*rt);
}
void slt(int *rs,int *rt,int *rd){
	(*rd) = ((*rs) < (*rt))?1:0;
}
void xor(int *rs,int *rt,int *rd){
	*rd = (*rs) ^ (*rt);
}
void mult(int *rs, int *rt,  int *HI,  int *LO){
	long long int temp_rs = *rs;
	long long int temp_rt = *rt;
	long long int res = temp_rs*temp_rt;
	*HI =(res&MASK_HI) >> 32;
	*LO =(res&MASK_LO);
}
void Div(int *rs, int *rt, int *HI,  int *LO){
	*HI = (*rs) % (*rt);
	*LO = (*rs) / (*rt);
}
void addi(int *rs,int *rt, short imm){
	if(imm < 0){
		rt ++;
		*rt = (*rs) + imm;
	
	}
	else{
		(*rt) = (*rs) + imm;
	}
}
void decode_lw(int *base,int *rt,short offset,memoire *m){
	*rt = lw((*base)+ offset,m);
}
void decode_sw(int *base,int *rt,short offset,memoire *m,int *taille_meme){
	sw((*base)+ offset,*rt,m,taille_meme);
}
void beq(int *rs,int *rt,short offset, int *PC){
	if(offset < 0){
		rt++;
		if ((*rs) == (*rt)){
			(*PC)= (*PC) + (offset << 2);
		}
	}
	else
	{
		if ((*rs) == (*rt)){
			(*PC)= (*PC) + (offset << 2);
		}
	}
}
void bne(int *rs,int *rt, short offset, int *PC){
	if(offset < 0){
		rt++;
		if ((*rs) != (*rt)){
			(*PC)= (*PC) + (offset << 2);
		}
	}
	else
	{
		if ((*rs) != (*rt)){
			(*PC)= (*PC) + (offset << 2);
		}
	}
	
}
void bgtz(int *rs,short offset, int *PC){
	if(offset < 0){
		rs++;
		if ((*rs) > 0){
		*PC+= (offset << 2);
		}
	}
	else{
		if ((*rs) > 0){
		*PC+= (offset << 2);
		}
	}
	
}
void blez(int *rs,short offset, int *PC){
	if(offset < 0){
		rs++;
		if ((*rs) <= 0){
		(*PC)+= (offset << 2);
		}
	}
	else
	{
		if ((*rs) <= 0){
		(*PC)+= (offset << 2);
		}
	}
}
void lui(int *rt,int im){
	*rt = im << 16;
}
void rotr(int *rt,int *rd,int sa){
	*rd = (((*rt) >> sa) | ((*rt) << (32 - sa)));
}
void sll(int *rt, int *rd, int sa){
	*rd = (*rt) << sa;
}
void srl(int *rt, int *rd, int sa){
	*rd = (*rt) >> sa;
}
void jr(int *rs,int *PC){
	*PC = *rs;
}
void mflo(int *rd,int *LO){
	*rd = *LO;
}
void mfhi(int *rd,int *HI){
	*rd = *HI;
}