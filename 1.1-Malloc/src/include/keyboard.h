#ifndef KEYBOARD_H
#define KEYBOARD_H

enum {
	ESC=27,
	BACK=8,
	TAB=9,
	ENTER='\n'
};

void keyboard(uint8_t scancode);

void clear_key();
char get_key();

#endif //KEYBOARD_H

