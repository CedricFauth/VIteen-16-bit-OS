/*
-----------------------------------------------
        VIteen OS v1.0 by Cedric Fauth
-----------------------------------------------
*/

#include "libc.h"


main_c(){

    clear_screen();

    PRINTS("[ VIteen OS                                      v1.0 ]");
    DEBUGS("[ DEBUG                 ]");

    DEBUGS("Configure keyboard...\n");
    config_keyboard();

    DEBUGS("Enable IRQ...\n");
    IRQ_set_mask(0); // disable timer
    register_irq();

    DEBUGS("Registers:\n");
    debug_segments();
    DEBUGS("\nDone.\n");

    for (;;) PRINTC(getch());

    DEBUGS("GOING 2 SLEEP");
    sleep();
    for(;;);
}
