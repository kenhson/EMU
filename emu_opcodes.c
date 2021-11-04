group_t opcode_table;
for (int i = 0; i < 255; i++) opcode_table[i] = &nop;

opcode_table[0x3A] = &ld_a_nn_a; // LD A (nn) 
opcode_table[0x32] = &ld_a_nn_a; // LD (nn) A

opcode_table[0x47] = &ld_r_r; // A>B
opcode_table[0x78] = &ld_r_r; // B>A
opcode_table[0x7C] = &ld_r_r; // H>A
opcode_table[0x7D] = &ld_r_r; // L>A
opcode_table[0x67] = &ld_r_r; // A>H
opcode_table[0x6F] = &ld_r_r; // A>L

opcode_table[0x3E] = &ld_r_n; // A
opcode_table[0x36] = &ld_r_n;

opcode_table[0x3C]= &inc_r; // A
opcode_table[0x04]= &inc_r; // B
opcode_table[0x24]= &inc_r; // H
opcode_table[0x2C]= &inc_r; // L

opcode_table[0x3D]= &dec_r; // A
opcode_table[0x05]= &dec_r; // B
opcode_table[0x25]= &dec_r; // H
opcode_table[0x2D]= &dec_r; // L

opcode_table[0x00]= &nop;
opcode_table[0xF3]= &di; // disable interupt
opcode_table[0xFB]= &ei; // enable interupt

opcode_table[0xAF]= &xor_n; // A
opcode_table[0xA8]= &xor_n; // B
opcode_table[0xA9]= &xor_n; // C
opcode_table[0xAA]= &xor_n; // D
opcode_table[0xAB]= &xor_n; // E
opcode_table[0xAC]= &xor_n; // H
opcode_table[0xAD]= &xor_n; // L

opcode_table[0xC3]= &jp_nn; // L

opcode_table[0xD3]= &out_in; // OUT
opcode_table[0xDB]= &out_in; // IN

opcode_table[0x01]= &ld_dd_nn; // BC
opcode_table[0x11]= &ld_dd_nn; // DE
opcode_table[0x21]= &ld_dd_nn; // HL
opcode_table[0x31]= &ld_dd_nn; // SP

opcode_table[0xED]= &ldir; // ed table

opcode_table[0x20]= &jr_cc_e;
group_t opcode_table_ed;
for (int i = 0; i < 255; i++) opcode_table_ed[i] = &nop;

// opcode_table_ed[0xB0]= &ed;
