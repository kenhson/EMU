#include <stdio.h>
#include <string.h>
#include "emu.h"

enum opcode_enum {NOP};
const enum opcode_enum INC_A = 0x3C;
const enum opcode_enum DEC_A = 0x3D;
const enum opcode_enum LD_NN_A = 0x32;
const enum opcode_enum LD_A_NN = 0x3A;
const enum opcode_enum LD_A_B = 0x47;
const enum opcode_enum LD_B_A = 0x78;
const enum opcode_enum LD_A_N = 0x3E;
const enum opcode_enum LD_B_N = 0x36;
const enum opcode_enum DI = 0xF3;
const enum opcode_enum EI = 0xFB;
const enum opcode_enum XOR_A = 0xAF;
const enum opcode_enum JP_NN = 0xC3;
const enum opcode_enum PORT_N_A = 0xD3;
const enum opcode_enum PORT_A_N = 0xDB;
const enum opcode_enum LD_DD_HL = 0x21;
const enum opcode_enum LD_DD_SP = 0x31;
const enum opcode_enum LD_DD_DE = 0x11;
const enum opcode_enum LD_DD_BC = 0x01;

unsigned char RAM[0x64000] = {[0 ... 0x7FFF] = 0, NOP, DI, XOR_A, PORT_N_A, 00, NOP, 
JP_NN, 0x74, 0x06, 0xEE, [0xC300 ... 0xCFFF] = '*'};

uint8_t opcode;
uint16_t pc;
void showStatus();
void showReg(); 
void loadGrid();
void showGrid();
void loadRom();

int main()
{
#include "emu_opcodes.c"
char key;
loadRom(); puts("e6feb2? \n");
pc = 0x8000; status = 0;

while(RAM[pc] != 0xEE)
	{
	pc = opcode_table[RAM[pc]](RAM[pc]);
	showReg();
	showStatus();
	printf(", pc = %X \n", pc);
	scanf("%1c", &key);
	}
showGrid();
}

#include "emu_functions.c"
#include "emu_rom.c"

// set flag
void setFlag(enum flags param1, bool param2) // setFlag(neg,1);
{
if (param2 == 1) {status = status | param1; } else {status = status &~ param1; }
}

// get flag
bool getFlag(enum flags param1) // getFlag(neg);
{
if ( (status & param1) > 0) return 1;  else  return 0; 
}

// showStatus
void showStatus(){
if (getFlag(carry)==1) printf("carry=%c ", '1'); else printf("carry=%c ",'0');
if (getFlag(neg)==1) printf("neg=%c ", '1'); else printf("neg=%c ",'0');
if (getFlag(overflow)==1) printf("p/v=%c ", '1'); else printf("p/v=%c ",'0');
if (getFlag(halfCarry)==1) printf("halfCarry=%c ", '1'); else printf("halfCarry=%c ",'0');
if (getFlag(zero)==1) printf("zero=%c ", '1'); else printf("zero=%c ",'0');
if (getFlag(sign)==1) printf("sign=%c ", '1'); else printf("sign=%c ",'0');
}

// showReg
void showReg(){
printf(" ...reg.A = %d, \n", reg.A);
}

// loadGrid
void loadGrid()
{
	for (int i = 0; i<64; i++)
	RAM[0xC300+i] = 42; //*
}

// showGrid
void showGrid()
{
	int counter =0;
	for (int j =0; j < 8; j++)
	{
		for (int i = 0; i<8; i++)
		{
		printf("%c", RAM[0xC300+counter]);
		counter++;
		}
	printf("\n");
	}
}

