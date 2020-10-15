ASM=nasm
CC=bcc

all: os clean

bootloader.bin: boot/io.asm boot/log.asm boot/bootloader.asm
	$(ASM) -f bin boot/bootloader.asm -o bootloader.bin -iboot/

test.o: kernel/kernel.c
	$(CC) -ansi -0 -c -o test.o kernel/kernel.c
	
libc.o: kernel/libc.asm
	nasm -f as86 -o libc.o kernel/libc.asm

kernel.o: kernel/start.asm
	nasm -f as86 -o kernel.o kernel/start.asm

kernel.bin: kernel.o libc.o test.o
	ld86 -d -o kernel.bin kernel.o test.o libc.o

.PHONY: os qemu clean cleanall
os: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os.bin

qemu: os clean
	qemu-system-x86_64 -curses -drive file=os.bin,index=0,if=floppy,format=raw

clean:
	rm -f *.o bootloader.bin kernel.bin

cleanall:
	rm -f *.o *.bin
