#include "libc.h"

/*
	I/O BEGIN
*/

#define NUM_ROWS 25
#define NUM_COLS 80

static uint8_t cur_row = 0, cur_col = 0;

void update_cursor() {
	short pos = cur_row * NUM_COLS + cur_col;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void clear_screen(){
	int i = 0;
	for (i = 0; i < NUM_ROWS*NUM_COLS; i = i+1) {
		cga_setchar(0x0700 + ' ', i);
	}
	cur_row = 0;
	cur_col = 0;
	update_cursor();
}

// does not update cursor
void put(char c) {
	short pos = cur_row*NUM_COLS+cur_col;
	short cell = 0x0700 + c;
	cga_setchar(cell, pos);
	if ((cur_col+1) % NUM_COLS == 0) {
		cur_row = cur_row + 1;
	}
	cur_col = (cur_col+1) % NUM_COLS;
}

void putchar(char c) {
	put(c);
	update_cursor();
}

void prints(char *s) {
	while(*s != '\0') {
		put(*s);
		s = s+1;
	}
	update_cursor();
}

/*
	I/O END
*/
