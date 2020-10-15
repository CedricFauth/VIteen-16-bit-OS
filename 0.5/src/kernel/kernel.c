/*
-----------------------------------------------
        VIteen OS v0.4 by Cedric Fauth
-----------------------------------------------
*/

extern void putchar();
extern void putchar2();
extern void printstr();

char a = 'A';
char *str = "\n\rHello World!";

int main_c(){

    char x = 'X';

    putchar(a);
    putchar(x);
    printstr(str);

    putchar2(x);

    return 0;
}
