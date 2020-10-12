---
has_children: false
has_toc: false
title: v0.4
---

# C code 
\
Run this version:
```
cd v0.4/src
nasm -f bin bootloader.asm -o bootloader.bin
qemu-system-x86_64 -curses -drive file=bootloader.bin,index=0,if=floppy,format=raw
```

TODO text
