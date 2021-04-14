/*
-----------------------------------------------
        VIteen OS v0.7 by Cedric Fauth
-----------------------------------------------
*/

#include "libc.h"

char smile[] = {1,0};

main_c(){

    clear_screen();
    PRINTS("[ VIteen OS                                      v0.9 ]");
    //PRINTS("Hello\n1\n2\n3\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWorld                 1234567890123456789012345678901234567890");
    //PRINTX(1);
    DEBUGS("[ DEBUG               "); DEBUGS(smile); DEBUGS(" ]");
    //DEBUGS("Hello\n1\n2\n3\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWorld                 123456789012345678901234567890");

    DEBUGS("Configure keyboard...\n");
    config_keyboard();
    DEBUGS("Enable IRQ...\n");
    register_irq();
    DEBUGS("Registers:\n");
    debug_segments();
    DEBUGS("\nDone.\n");

    sleep();
    for(;;);

    return 0;
}
