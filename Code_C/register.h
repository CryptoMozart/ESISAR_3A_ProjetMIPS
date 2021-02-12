#include "convert.h"
#include "memory.h"

#define MASK_special 0xFC000000 //OK
#define MASK_op_code 0x0000003F //OK
#define MASK_rs 0x03E00000 //OK
#define MASK_rt 0x001F0000 //OK
#define MASK_rd 0x0000F800 //OK
#define MASK_sa 0x000007C0
#define MASK_R 0x00200000
#define MASK_imm 0x0000FFFF

#define MASK_HI 0xFFFFFFFF00000000
#define MASK_LO 0x00000000FFFFFFFF


void Decode(int ligne,int REGISTRE[32], int *HO, int *LO,int *PC,memoire *m,int *taille_mem);

void add(int *rs,int *rt,int *rd);
void sub(int *rs,int *rt,int *rd);
void and(int *rs,int *rt,int *rd);
void or(int *rs,int *rt,int *rd);
void slt(int *rs,int *rt,int *rd);
void xor(int *rs,int *rt,int *rd);
void mult(int *rs, int *tr, int *HI, int *LO);
void Div(int *rs, int *rt,int *HI, int *LO);
void addi(int *rs,int *rt, short imm);
void beq(int *rs,int *rt,short offset, int *PC);
void bne(int *rs,int *rt, short offset, int *PC);
void bgtz(int *rs,short offset, int *PC);
void blez(int *rs,short offset, int *PC);
void decode_lw(int *base,int *rt,short offset,memoire *m);
//fait appel à la fonction lw qui se trouve dans le module memory
void decode_sw(int *base,int *rt,short offset,memoire *m,int *taille_mem);
//fait appel à la fonction sw qui se trouve dans le module memory
void lui(int *rt,int offset);
void rotr(int *rt,int *rd,int sa);
void sll(int *rt, int *rd, int sa);
void srl(int *rt, int *rd, int sa);
void jr(int *rs,int *PC);
void mflo(int *rd,int *LO);
void mfhi(int *rd,int *HI);