---
has_children: false
has_toc: false
title: v0.2
---

**Goal of v0.2:**

Run this version:
```
cd v0.2/src
TODO
```

## Printing bootloader information

v0.2 is all about writing functions to print useful information (before loading the actual kernel etc.). Since I don't care about the bootloader's speed we print strings character by character using pre-build BIOS routines. This works by loading a character's ASCII value into a register and triggering an interrupt which activates a BIOS routine. The BIOS routine writes the character into the CGA Screen's memory which means we'll see it on our monitor.

After achieving this single character print can write an assembly routine that prints C-style strings (a '\0' terminated array of chars). The idea is to print each character one at a time until a 0x0 is detected. After that, we stop the routine.

Now that our printstr function works there is another important function we need - printing integers. Integers aren't in ASCII form so the idea is to store an ASCII representation of an integer value and print that buffer with our printstr routine. This is a bit more complicated but quite interesting. For simplicity, we only write a printhex function that will print integers in hexadecimal. The algorithm works by taking 4 bits (of a 16-bit integer value) at a time, converting them into an ASCII value ('0'-'9','a'-'f'), and storing this at a specific position in a buffer. Repeating these steps 4 times will convert a whole 16-bit integer into a 4-byte character string.

TODO: algorithm examples

After implementing the printstr and printhex routines we can print the start addresses of CS, SS, DS, and ES.
