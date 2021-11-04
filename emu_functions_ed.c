// ed b0 ldir
uint16_t ed(uint8_t opcode){
	while (reg.BC != 0){
	RAM[reg.DE] = RAM[reg.HL]; printf("%x %x ... ", RAM[reg.HL], RAM[reg.DE]);
	reg.DE++ ; reg.HL++;
	reg.BC--;
	}
	return ++pc;

	}
