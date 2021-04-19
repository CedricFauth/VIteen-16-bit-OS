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
    int i,j;
    char c;
    char *buff = 1, *buff2, *buff4;
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

    /*
    for (i = 1; i != 0x21; i = i+1) {
        buff = malloc(sizeof(char) * 0x3FC);
        PRINTX(i); PRINTC(':'); PRINTX(buff); PRINTC(' ');
    }

    print_heap();

    for(j = 0; j != i; j = j+1) {
        free(buff-0x400*j);
    }*/
    // testing and leaving 1 byte left (+2*4 blocks)
    buff = malloc(sizeof(char) * (0x8000-9));
    print_heap();
    free(buff);

    print_heap();
    
    //PRINTX(sum(1,100));
    while ('q' != (c = getch())) PRINTC(c);

    DEBUGS("\nGOING 2 SLEEP\n");
    sleep();
    for(;;);
}
