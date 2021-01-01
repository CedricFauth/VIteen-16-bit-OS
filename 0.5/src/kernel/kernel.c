/*
-----------------------------------------------
        VIteen OS v0.5 by Cedric Fauth
-----------------------------------------------
*/

extern void putchar();
extern void putchar2();
extern void printstr();

char a = 'A';
char *str = "\n\rHello World!";

short cell2 = 0x3541 & 0xFFFF;

int main_c(){

    char x = 'X';

    putchar(a);
    putchar(x);
    printstr(str);

    putchar2(cell2);

    return 0;
}
