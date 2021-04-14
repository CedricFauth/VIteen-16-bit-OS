#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "libc.h"

enum {
	ESC=27,
	BACK=8,
	TAB=9,
	ENTER=13
};

void keyboard(uint8_t scancode);

#endif //KEYBOARD_H

