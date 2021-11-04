#include <stdint.h> // uint8_t
#include <stddef.h>

//unsigned char ROM[0x2FFF];

typedef uint16_t (*group_t [255])(uint8_t); // opcodes


signed char n;
wchar_t nn;
uint8_t port;
uint16_t PC;

typedef struct{
signed char A, B, C, D, E, H, L, HLp;
signed char a, b, c, d, e, h, l, hl;
wchar_t BC, DE, HL, SP;

}reg_t; reg_t reg;

enum {
A = 7, HLp = 6, L = 5, H = 4, E = 3, D = 2, C = 1, B = 0,
a = 7, hl = 6, l = 5, h = 4, e = 3, d = 2, c = 1, b = 0,
BC = 0, DE = 1, HL = 2, SP = 3
};

#include <stdbool.h>

uint16_t nop(uint8_t);
uint16_t ld_r_n(uint8_t);
uint16_t ld_r_r(uint8_t);
uint16_t inc_r(uint8_t);
uint16_t dec_r(uint8_t);
uint16_t ld_a_nn_a(uint8_t);
uint16_t ld_a_nn_a(uint8_t);
uint16_t di(uint8_t);
uint16_t ei(uint8_t);
uint16_t xor_n(uint8_t);
uint16_t jp_nn(uint8_t);
uint16_t out_in(uint8_t);
uint16_t ld_dd_nn(uint8_t);
uint16_t ed(uint8_t); // ed table
uint16_t ldir(uint8_t);
uint16_t jr_cc_e(uint8_t);

enum flags
	{
	carry = 	( 1 << 0 ),
	neg = 		( 1 << 1 ),
	overflow = 	( 1 << 2 ),
	parity = 	( 1 << 2 ),
	unused1 = 	( 1 << 3 ),
	halfCarry = 	( 1 << 4 ),
	unused2 = 	( 1 << 5 ),
	zero = 		( 1 << 6 ),
	sign =	 	( 1 << 7 ),
	};

uint8_t status; 
bool boo;
void setFlag(enum flags, bool ); // bool will be 1 or 0
bool getFlag(enum flags); // boo = here i.e. carry
