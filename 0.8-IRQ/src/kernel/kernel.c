/*
-----------------------------------------------
        VIteen OS v0.7 by Cedric Fauth
-----------------------------------------------
*/

#include "libc.h"

char smile[] = {1,0};

main_c(){

    clear_screen();
    PRINTS("[ VIteen OS                                      v0.7 ]");
    //PRINTS("Hello\n1\n2\n3\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWorld                 1234567890123456789012345678901234567890");
    //PRINTX(1);
    DEBUGS("[ DEBUG               "); DEBUGS(smile); DEBUGS(" ]");
    //DEBUGS("Hello\n1\n2\n3\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWorld                 123456789012345678901234567890");

    config_keyboard();
    register_irq();
    debug_segments();

    sleep();
    for(;;);

    return 0;
}
