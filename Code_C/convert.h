#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* On définie les opcodes pour chaque instructions dans le header. Cela rend le code plus lisible et plus clair 
quand nous convertissons les instrucions */

#define op_add 32
#define op_sub 34
#define op_and 36
#define op_or 37
#define op_xor 38
#define op_slt 42
#define op_addi 8
#define op_lw 35
#define op_sw 43
#define op_beq 4
#define op_bne 5
#define op_lui 15
#define op_bgtz 7
#define op_blez 6
#define op_jr 8
#define op_mflo 18
#define op_mfhi 16
#define op_srl 2
#define op_rotr 2
#define op_mult 24
#define op_div 26
#define op_j 2
#define op_jal 3
#define op_sll 0

void convert(char *rfile, char *wfile);
int convert_interactive(char *opcode);
