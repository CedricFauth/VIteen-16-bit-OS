---
has_children: false
has_toc: false
title: v0.3
---

# Loading sectors from disk (bootloader) 
\
**Goal of v0.3: Loading sectors from disk. Currently the BIOS only loads 512 bytes of code from disk. This isn't enough as we will see later.**

Run this version:
```
cd v0.3/src
nasm -f bin bootloader.asm -o bootloader.bin
qemu-system-x86_64 -drive file=bootloader.bin,index=0,if=floppy,format=raw
```

![](https://user-images.githubusercontent.com/25117793/95678531-8efbcd00-0bcd-11eb-9b97-f92d2b8532c3.png)

Since the bootloader is limited by 512 Bytes in size we cannot write much more code without considering that fact. This part is about loading more segments from disk into memory. First, we extend the size of the bootloader file to 3x512B. The first 512B contain our code. The last 2 sectors (2x512B) contain random data. When booting from this file only 512B will be loaded in memory and executed. Next, we extend our code with calling a bios routine. The BIOS helps us loading more sectors from disk to a given address in memory. This version of the OS loads 2 sectors from disk nad prints the first word of each sector.
