// nop 00
uint16_t nop(uint8_t opcode){
        printf("NOP");
        return ++pc;
        }

// jr_cc_e
uint16_t jr_cc_e(uint8_t opcode){
puts("inside jr_cc_e");
}

// ldir ed
uint16_t ldir(uint8_t opcode){
	puts("LDIR");
	pc++; opcode = RAM[pc]; ed(opcode);
	return pc;
	}

// ld_dd_nn
uint16_t ld_dd_nn(uint8_t opcode){
	pc++; unsigned char bytelo = RAM[pc];
	pc++; unsigned char bytehi = RAM[pc];
	wchar_t address = (bytehi << 8 | bytelo);
	switch (opcode >> 4)
		{
		case BC: reg.BC = address; printf("LD BC %X", address); break;
		case DE: reg.DE = address; printf("LD DE %X", address); break;
		case HL: reg.HL = address; printf("LD HL %X", address); break;
		case SP: reg.SP = address; printf("LD SP %X", address); break;
		default: puts("error in ld_dd_nn");
		}
		return ++pc;
}

// port d3 db
uint16_t out_in(uint8_t opcode){
	pc++; port = RAM[pc]; // port FF for VG
	if (opcode == 0xD3) {printf("PORT OUT %X", port);}
	if (opcode == 0XDB) {reg.A = port; printf("PORT IN %X", port);}
	return ++pc;
}

// jp_nn c3
uint16_t jp_nn(uint8_t opcode){
        pc++; unsigned char bytelo = RAM[pc];
        pc++; unsigned char bytehi = RAM[pc];
        wchar_t address = (bytehi << 8 | bytelo);
        pc = address; 
	printf("JP to %x", address);
	return pc;
        }


// xor_n af a8 a9 aa ab ac ad
uint16_t xor_n(uint8_t opcode){
        switch (opcode &7)
                {
                case A: { reg.A = reg.A & reg.A; printf("XOR_A"); break; };
                case B: { reg.A = reg.A & reg.B; printf("XOR_B"); break; };
                case C: { reg.A = reg.A & reg.C; printf("XOR_C"); break; };
                case D: { reg.A = reg.A & reg.D; printf("XOR_D"); break; };
                case E: { reg.A = reg.A & reg.E; printf("XOR_E"); break; };
                case H: { reg.A = reg.A & reg.H; printf("XOR_H"); break; };
                case L: { reg.A = reg.A & reg.L; printf("XOR_L"); break; };
                //default: { puts("error in switch xor_n"); }
                }
        setFlag(carry,0); setFlag(neg,0); setFlag(halfCarry,0);
	if (reg.A == -128 || reg.A == 127) setFlag(overflow,1); else setFlag(overflow,0);
	if (reg.A == 0) setFlag(zero,1); else setFlag(zero,0);
	if (reg.A < 0) setFlag(sign,1); else setFlag(sign,0);

	return ++pc;
        }

// di
uint16_t di(uint8_t opcode){
	printf("DI");
	return++pc;
}

// ei
uint16_t ei(uint8_t opcode){
	printf("EI");
	return++pc;
}

// dec
uint16_t dec_r(uint8_t opcode){
        signed char temp;
        switch (opcode >> 3 & 7)
                {
                case A: temp = --reg.A; printf("DEC A"); break;
                case B: temp = --reg.B; printf("DEC B"); break;
                case H: temp = --reg.H; printf("DEC H"); break;
                case L: temp = --reg.L; printf("DEC L"); break;
                }
setFlag(neg,1); 
if (temp == 127) setFlag(overflow,1); else setFlag(overflow,0);
if (temp == 0) setFlag(zero,1); else setFlag(zero,0);
if (temp < 0) setFlag(sign,1); else setFlag(sign,0);
if (temp == 15) setFlag(halfCarry,1); else setFlag(halfCarry,0);
return ++pc;
}

// inc
uint16_t inc_r(uint8_t opcode){
        signed char temp;
        switch (opcode >> 3 & 7)
                {
                case A: temp = ++reg.A; printf("INC A"); break;
                case B: temp = ++reg.B; printf("INC B"); break;
                case H: temp = ++reg.H; printf("INC H"); break;
                case L: temp = ++reg.L; printf("INC L"); break;
                }
setFlag(neg,0);
if (temp == -128) setFlag(overflow,1); else setFlag(overflow,0);
if (temp == 0) setFlag(zero,1); else setFlag(zero,0);
if (temp < 0) setFlag(sign,1); else setFlag(sign,0);
if (temp == 16) setFlag(halfCarry,1); else setFlag(halfCarry,0);
return ++pc;
}

// ld_r_n 3E 2E 36 46 1E 16 0E 06
uint16_t ld_r_n(uint8_t opcode)
        {
        pc++;
        n=RAM[pc];
        switch ((opcode >> 3) &7)
                {
                case A: { reg.A = n; printf("LD A %d", n); break; };
                case B: { reg.B = n; printf("LD B %d", n); break; };
                case C: { reg.C = n; printf("LD C %d", n); break; };
                case D: { reg.D = n; printf("LD D %d", n); break; };
                case E: { reg.E = n; printf("LD E %d", n); break; };
                case H: { reg.H = n; printf("LD H %xh", n); break; };
                case L: { reg.L = n; printf("LD L %xh", n); break; };
                case HLp:{ reg.HLp = n; printf("LD (HL) %xh", n); break; };
                default: { puts("error in switch ld_r_n"); }
                }
        return ++pc;
        }

// ld_r_r
uint16_t ld_r_r(uint8_t opcode)
        {
        signed char trans;
        switch  (opcode & 7) // source
                {
                case A: trans = reg.A; printf("LD r A "); break; // source is A reg
                case B: trans = reg.B; printf("LD r B "); break;
                case H: trans = reg.H; printf("LD r H "); break;
                case L: trans = reg.L; printf("LD r L "); break;
                default:{ puts("ld_r_r source reg not found"); }
                }
        switch (opcode >> 3 & 7) // destination
                {
                case A: reg.A = trans; printf("dest is A"); break;
                case B: reg.B = trans; printf("dest is B"); break;
                case H: reg.H = trans; printf("dest is H"); break;
                case L: reg.L = trans; printf("dest is L"); break;
                default:{ puts("ld_r_r dest reg not found"); }
                }
        return  ++pc;
        }

// ld_a_nn_a
uint16_t ld_a_nn_a(uint8_t opcode){
        pc++; unsigned char bytelo = RAM[pc];
        pc++; unsigned char bytehi = RAM[pc];
        wchar_t address = (bytehi << 8 | bytelo);
        switch (opcode >> 3 & 1)
                {
                case 1: reg.A = RAM[address]; printf("LD A (%X) ", address); break;
                case 0: RAM[address] = reg.A; printf("LD (%X) A ", address); break;
                }
        return ++pc;
        }

