#ifndef LIBC_H
#define LIBC_H

#include "types.h"

typedef struct screen screen_t;
extern screen_t scr_m;
extern screen_t scr_d;

#define PRINTS(x) prints(x, &scr_m)
#define PRINTX(x) printx(x, &scr_m)
#define DEBUGS(x) prints(x, &scr_d)
#define DEBUGX(x) printx(x, &scr_d)

// functions in libc.ASM
extern void outb(uint8_t value, uint16_t port);
extern void cga_setcell(uint16_t cell, uint16_t position);
extern void cga_moveup(uint16_t pos, uint16_t offset);

// functions in libc.C
void clear_screen();
//void putchar(char c);
void prints(char *s, screen_t *scr);
void printx(uint16_t val, screen_t *scr);

#endif //LIBC_H
