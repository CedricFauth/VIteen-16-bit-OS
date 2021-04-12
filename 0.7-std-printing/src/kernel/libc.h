#ifndef LIBC_H
#define LIBC_H

#include "types.h"

// functions in libc.ASM
extern void cga_setchar(uint16_t cell, uint16_t position);
extern void outb(uint8_t value, uint16_t port);

// functions in libc.C
void clear_screen();
void putchar(char c);
void prints(char *s);

#endif //LIBC_H
