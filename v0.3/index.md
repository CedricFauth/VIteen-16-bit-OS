---
has_children: false
has_toc: false
title: v0.3
---

# Loading sectors from disk (bootloader)

**Goal of v0.3: Loading sectors from disk. Currently the BIOS only loads 512 bytes of code from disk. This isn't enough as we will see later.**

Run this version:
```
cd v0.3/src
nasm -f bin bootloader.asm -o bootloader.bin
qemu-system-x86_64 -curses -drive file=bootloader.bin,index=0,if=floppy,format=raw
```

TODO text
