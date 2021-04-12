/*
-----------------------------------------------
        VIteen OS v0.6 by Cedric Fauth
-----------------------------------------------
*/

//extern void bios_putchar();
//extern void bios_printstr();

extern void vga_putchar();
extern void outb();

char a = 'A';
char *str = "\n\rHello World!";

short cell2 = 0x07 * 0x100 + 0x36;// & 0xFFFF;

void display(char c, int row, int col) {
    short cell, pos;
    cell = 0x0700 + c;
    pos = (row*80+col)*2;
    vga_putchar(cell, pos);
}

main_c(){
    int i,j;
    char x;
    
    x = 'X';

    for (i = 0; i < 15; i = i+1) {
        for (j = 0; j < 80; j = j+1){
            display('x', i, j);
        }
    }

    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);

    return 0;
}
