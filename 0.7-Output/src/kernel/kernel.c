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
    PRINTS("Hello\n1\n2\n3\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWorld                 123456789123456789123456789123456");
    
    PRINTX(100);

    DEBUGS("[ DEBUG               "); DEBUGS(smile); DEBUGS(" ]");
    DEBUGS("Hello\n1\n2\n3\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nWorld                 123456789123456789123456789");

    for(;;);

    return 0;
}
