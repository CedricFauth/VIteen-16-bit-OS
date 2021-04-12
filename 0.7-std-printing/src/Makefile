ASM=nasm
CC=bcc

all: os clean

bootloader.bin: boot/io.asm boot/log.asm boot/bootloader.asm
	$(ASM) -f bin boot/bootloader.asm -o bootloader.bin -iboot/

kernel.o: kernel/kernel.c
	$(CC) -ansi -0 -c -o kernel.o kernel/kernel.c

libc.o: kernel/libc.c
	$(CC) -ansi -0 -c -o libc.o kernel/libc.c

libc_asm.o: kernel/libc.asm
	$(ASM) -f as86 -o libc_asm.o kernel/libc.asm

start_kernel.o: kernel/start.asm
	$(ASM) -f as86 -o start_kernel.o kernel/start.asm

kernel.bin: start_kernel.o libc.o libc_asm.o kernel.o
	ld86 -d -o kernel.bin start_kernel.o kernel.o libc.o libc_asm.o

.PHONY: os qemu clean cleanall
os: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os.bin

qemu: os clean
	qemu-system-x86_64 -curses -drive file=os.bin,index=0,if=floppy,format=raw

clean:
	rm -f *.o bootloader.bin kernel.bin

cleanall:
	rm -f *.o *.bin
