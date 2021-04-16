#include "libc.h"
#include "keyboard.h"


#define NUM_ROWS 25
#define NUM_COLS 80

#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

struct screen {
	enum {
		MAIN, DEBUG
	} type;
	uint16_t start_r;
	uint16_t start_c;
	uint16_t end_r;
	uint16_t end_c;
	uint16_t color;
	// private; reset with clear_screen
	uint16_t row;
	uint16_t col;
};

screen_t scr_m = {MAIN,  0,  0, 25, 55, 0x0700};
screen_t scr_d = {DEBUG, 0, 55, 25, 80, 0x6000};

void update_cursor() {
	short pos = scr_m.row * NUM_COLS + scr_m.col;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void clear_screen(){
	int i, j;

	scr_m.row = scr_m.start_r;
	scr_m.col = scr_m.start_c;
	scr_d.row = scr_d.start_r;
	scr_d.col = scr_d.start_c;

	for (i = scr_m.start_r; i < scr_m.end_r; i = i+1) {
		for (j = scr_m.start_c; j < scr_m.end_c; j = j+1) {
			cga_setcell(scr_m.color + ' ', i*NUM_COLS+j);
		}
	}
	for (i = scr_d.start_r; i < scr_d.end_r; i = i+1) {
		for (j = scr_d.start_c; j < scr_d.end_c; j = j+1) {
			cga_setcell(scr_d.color + ' ', i*NUM_COLS+j);
		}
	}
	
	update_cursor();
}

// does not update cursor
void put(char c, screen_t *scr) {
	short pos, i, j;
	if (c == '\n') {
		scr->col = scr->start_c;
		scr->row = scr->row + 1;
	} else if (c == '\r') {
		scr->col = scr->start_c;
	} else if (c == TAB) {
		scr->col = (scr->col/4+1) * 4;
	} else if (c == BACK) {
		// top left corner
		if (scr->col == scr->start_c && scr->row == scr->start_r+1) {
			return;
		// left border
		} else if (scr->col == scr->start_c) {
			scr->row = scr->row-1;
			scr->col = scr->end_c;
			while (scr->col > scr->start_c
				&& cga_getcell(scr->row*NUM_COLS+scr->col-1) == ' ')
			{
				scr->col = scr->col-1;
			}
			if (scr->col == scr->end_c) scr->col = scr->col -1;
		// anywhere else
		} else {
			scr->col = scr->col - 1;
		}
		cga_setcell(scr->color + ' ', scr->row*NUM_COLS+scr->col);
	} else if (c == '\0') {
		return;
	} else {
		pos = scr->row*NUM_COLS+scr->col;
		cga_setcell(scr->color + c, pos);
		scr->col = scr->col + 1;
	}

	// after last col
	if (scr->col >= scr->end_c) {
		scr->col = scr->start_c;
		scr->row = scr->row + 1;
	}
	
	// after last row
	if (scr->row >= scr->end_r) {
		scr->row = scr->end_r - 1;
		scr->col = scr->start_c;
		for (i = scr->start_r+2; i < scr->end_r; i = i+1) {
			for (j = scr->start_c; j < scr->end_c; j = j+1) {
				cga_moveup(i*NUM_COLS+j, NUM_COLS);
			}
		}
		for (j = scr->start_c; j < scr->end_c; j = j+1) {
			cga_setcell(scr->color + ' ', (scr->end_r-1)*NUM_COLS+j);
		}
	}
}

void putchar(char c, screen_t *scr) {
	put(c, scr);
	update_cursor();
}


void printx(uint16_t val, screen_t *scr) {
	uint16_t tmp, i;
	uint8_t none = 1;
	put('0', scr);
	put('x', scr);
	for (i = 0; i < 4; i = i+1) {
		tmp = val >> ((3-i)*4);
		tmp = tmp & 0xF;
		if(!none || tmp) {
			none = 0;
			if (tmp < 10) {
				put('0'+tmp, scr);
			} else {
				put('A'+tmp-10, scr);
			}
		}
	}
	if (none) put('0',scr);
	update_cursor();
}

void prints(char *s, screen_t *scr) {
	while(*s != '\0') {
		put(*s, scr);
		s = s+1;
	}
	if (scr->type == MAIN) {
		update_cursor();
	} 
}

void IRQ_set_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline = IRQline - 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}

char getch() {
	char k;
	clear_key();
	//DEBUGS("stop\n");
	while(!(k = get_key()))
		stopping();
	return k;
}

// only gets called if keyboard interrupt
void irq() { 
	uint8_t scancode;
	//DEBUGS("irq\n");
	// wait for input
	while (inb(0x64) & 0x1 == 0) {}
	// read input
	scancode = inb(0x60);
	keyboard(scancode);

	outb(0x20, 0x20); // interrupt done
}
