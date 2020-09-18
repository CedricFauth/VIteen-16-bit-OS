---
has_children: false
has_toc: false
title: v0.1
---

# Booting something

The goal is to build a 16-bit operating system (kernel) that is programmable using C.

## Real and protected mode

Every Intel x86 CPU starts in something called 'real mode' which a 16-bit mode where the CPU behaves like Intel's first x86 chip - the 8086. This mode enables backward compatibility so that old operating systems written for 16-bit architectures are still able to boot on modern CPUs. Today's operating systems are using boot loaders to switch the CPU into 32-bit protected mode or 64-bit long mode before starting the actual OS. Real mode comes with some limitations...

### Real mode 'limitations' or challenges :)

* Less than 1MB of total RAM available (64kB for kernel and applications)
* No memory protection
* No virtual memory
* Only 16 bits of every register is usable
* Only one CPU Core runs in total
* ...

## Boot process

After starting a PC the BIOS (Basic Input/Output System), which is a firmware stored on the PC's Motherboard, takes over and performs hardware tests. The BIOS always runs in 16-bit real mode and therefore has direct access to the hardware. After successfully testing memory etc. BIOS tries to find bootable software on a boot device, such as a hard drive, CD, or floppy disk.

The BIOS looks up the first sector called boot sector of all storage devices until it finds an OS or boot loader. A sector has a size of 512 bytes. It can check whether or not code is marked as bootable by looking at the last word (16 bit = 2Byte) of a sector. If the last word is the so-called 'magic number' (which is 0xaa55) the BIOS knows this block is a boot block that actually contains code to run.

After identifying the boot sector, the whole sector gets loaded into memory at address 0x7c00 and the BIOS hands over control by giving the CPU the instruction to jump to 0x7c00 and run the boot sector's code.

