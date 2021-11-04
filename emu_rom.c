void loadRom()
{
puts("load ROM.BIN's into RAM");
int rom_ch;
FILE *fp;

fp = fopen("3001.BIN","r");
int counter = 0;

for (int i=0; i < 0x1000; i++)
	{
	rom_ch = fgetc(fp); 
	RAM[counter]=rom_ch;
	counter++;
	}
printf("%x", RAM[0x0FFF]);

fp = fopen("3002.BIN","r");

for (int i=0; i < 0x1000; i++)
	{
	rom_ch = fgetc(fp); 
	RAM[counter]=rom_ch;
	counter++;
	}
printf("%x", RAM[0x1FFF]);

fp = fopen("3003.BIN","r");

for (int i=0; i < 0x1000; i++)
	{
	rom_ch = fgetc(fp); 
	RAM[counter]=rom_ch;
	counter++;
	}
printf("%x \n", RAM[0x2FFF]);
}
