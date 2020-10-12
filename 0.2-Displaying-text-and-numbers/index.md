---
has_children: false
has_toc: false
title: v0.2
---

# Displaying text and numbers (bootloader)
\
**Goal of v0.2: Writing functions to display text and converting numbers to text**

Run this version:
```
cd 0.2-Displaying-text-and-numbers/src
nasm -f bin bootloader.asm -o bootloader.bin
qemu-system-x86_64 -curses -drive format=raw,file=bootloader.bin
```

![](https://user-images.githubusercontent.com/25117793/95678471-1ac12980-0bcd-11eb-94f8-e109ae5e2184.png)

## Printing bootloader information

v0.2 is all about writing functions to print useful information (before loading the actual kernel etc.). Since I don't care about the bootloader's speed we print strings character by character using pre-build BIOS routines. This works by loading a character's ASCII value into a register and triggering an interrupt which activates a BIOS routine. The BIOS routine writes the character into the CGA Screen's memory which means we'll see it on our monitor.

After achieving this single character print can write an assembly routine that prints C-style strings (a '\0' terminated array of chars). The idea is to print each character one at a time until a 0x0 is detected. After that, we stop the routine.

Now that our printstr function works there is another important function we need - printing integers. Integers aren't in ASCII form so the idea is to store an ASCII representation of an integer value and print that buffer with our printstr routine. This is a bit more complicated but quite interesting. For simplicity, we only write a printhex function that will print integers in hexadecimal. The algorithm works by taking 4 bits (of a 16-bit integer value) at a time, converting them into an ASCII value ('0'-'9','a'-'f'), and storing this at a specific position in a buffer. Repeating these steps 4 times will convert a whole 16-bit integer into a 4-byte character string.

Step by step example of the hex-to-string algorithm (only works for 16 bit numbers or less)
``` python
# initial configuration
buffer = '0x0000'
bx = 0xa100
ax = 0
i = 2
l = 4
# start:
# rotate bx to the right by 4 bit
bx = 0x100a
# get 0-4th LSB of bx (ax = bx & 0xf)
ax = 0x000a 
# if ax >= 0xa add 0x27
# then always add 0x30
# if ax >= 0xa then ax is now an ascii value from 'a' to 'f'
# else ax is now an ascii value from '0' to '9'
ax = 'a' # (0x61)
# next store the ascii value of ax in buffer[i]; i++
buffer = '0xa000'
# l--
# if l == 0: return
# else goto start

# output after 4th iteration:
buffer = '0xa100'
```

After implementing the printstr and printhex routines we can print the start addresses of CS, SS, DS, and ES.
