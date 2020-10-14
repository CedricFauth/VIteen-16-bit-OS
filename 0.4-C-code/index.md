---
has_children: false
has_toc: false
title: v0.4
---

# C code 
\
Run this version:
```
cd 0.4-C-code/src
make qemu
```

![](https://user-images.githubusercontent.com/25117793/95982833-ed6cb980-0e20-11eb-83ea-35fc08c4e972.png)

In this version we're finally using C. The C code will be our main kernel code later. In this version we're just calling a function that puts a character on the screen. After compiling the bootloader and the kernel seperately we append the kernel.bin at the end of the bootloader.bin. When the bootloader loads new sectors from disk these sectors will contain our kernel code. After loading the kernel.bin at address 0x8000 we can use a far jump to 0x800:0x0 (absolute address: 0x8000) to execute the kernel code.
