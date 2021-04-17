/*
-----------------------------------------------
        VIteen OS v1.0 by Cedric Fauth
-----------------------------------------------
*/

#include "libc.h"

// recursion test
int sum(int i, int limit){
    if (i >= limit) {
        debug_segments();
        return i;
    }
    return i + sum(i+1, limit);
}

struct mem {
    uint8_t mag;
    uint8_t data[];
}

//static uint8_t mem[0x8000] = {'a'};

main_c(){
    char c;

    clear_screen();
    PRINTS("[ VIteen OS                                      v1.0 ]");
    DEBUGS("[ DEBUG                 ]");
    debug_segments();

    DEBUGS("Configure keyboard...\n");
    config_keyboard();

    DEBUGS("Enable IRQ...\n");
    IRQ_set_mask(0); // disable timer
    register_irq();

    DEBUGS("Registers:\n");
    debug_segments();
    DEBUGS("\nDone.\n");

    DEBUGX(sizeof(char));

    //PRINTX(sum(1,100));
    while ('q' != (c = getch())) PRINTC(c);

    DEBUGS("\nGOING 2 SLEEP\n");
    sleep();
    for(;;);
}
