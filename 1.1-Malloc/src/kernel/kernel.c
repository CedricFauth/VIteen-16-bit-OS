/*
-----------------------------------------------
        VIteen OS v1.0 by Cedric Fauth
-----------------------------------------------
*/

#include "libc.h"
#include "mem.h"

// recursion test
int sum(int i, int limit){
    if (i >= limit) {
        debug_segments();
        return i;
    }
    return i + sum(i+1, limit);
}

main_c(){
    char c;
    char *buff, *buff2;
    clear_screen();
    PRINTS("[ VIteen OS                                      v1.0 ]");
    DEBUGS("[ DEBUG                 ]");
    debug_segments();

    DEBUGS("Configure keyboard...\n");
    config_keyboard();

    DEBUGS("Enable IRQ...\n");
    IRQ_set_mask(0); // disable timer
    register_irq();

    DEBUGS("Set up memory...\n");
    malloc_init();

    DEBUGS("Registers:\n");
    debug_segments();
    DEBUGS("\nDone.\n");

    print_heap();

    buff = malloc(sizeof(*buff)*4);
    buff[0] = 'H';
    buff[1] = 'i';
    buff[2] = '!';
    buff[3] = 0;
    print_heap();
    //PRINTS("buff at:"); PRINTX(buff);
    //PRINTS(buff);

    buff2 = malloc(sizeof(*buff2)*2);
    buff[0] = 'X';
    buff[1] = 0;
    print_heap();
    //PRINTS("buff2 at:"); PRINTX(buff2);
    //PRINTS(buff2);

    free(buff);

    print_heap();

    //free(buff2);

    //PRINTX(sum(1,100));
    while ('q' != (c = getch())) PRINTC(c);

    DEBUGS("\nGOING 2 SLEEP\n");
    sleep();
    for(;;);
}
