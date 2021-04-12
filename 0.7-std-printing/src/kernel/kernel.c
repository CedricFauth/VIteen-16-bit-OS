/*
-----------------------------------------------
        VIteen OS v0.7 by Cedric Fauth
-----------------------------------------------
*/

#include "libc.h"

char a = 'A';
char *str = "\n\rHello World!";

short cell2 = 0x07 * 0x100 + 0x36;// & 0xFFFF;

main_c(){
    int i,j;
    char x;
    
    x = 'X';

    clear_screen();
    prints("Hello World                                          123456789123456789123456789");
    prints("Hello World                                          123456789123456789123456789");
    putchar('Z');
    return 0;
}
