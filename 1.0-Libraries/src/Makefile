ASM=nasm
CC=bcc
ARGS=-Iinclude/ -ansi -0 -c

all: os clean

bootloader.bin: boot/io.asm boot/log.asm boot/bootloader.asm
	$(ASM) -f bin boot/bootloader.asm -o bootloader.bin -iboot/

kernel.o: kernel/kernel.c
	$(CC) $(ARGS) -o kernel.o kernel/kernel.c

keyboard.o: lib/keyboard.c
	$(CC) $(ARGS) -o keyboard.o lib/keyboard.c

libc.o: lib/libc.c
	$(CC) $(ARGS) -o libc.o lib/libc.c

libc_asm.o: lib/libc.asm
	$(ASM) -f as86 -o libc_asm.o lib/libc.asm

start_kernel.o: kernel/start.asm
	$(ASM) -f as86 -o start_kernel.o kernel/start.asm

kernel.bin: start_kernel.o libc.o libc_asm.o kernel.o keyboard.o
	ld86 -0 -d -o kernel.bin start_kernel.o kernel.o libc.o libc_asm.o keyboard.o

.PHONY: os qemu clean cleanall
os: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os.bin

qemu: os clean
	qemu-system-x86_64 -L "./pc-bios" -curses -drive file=os.bin,index=0,if=floppy,format=raw

clean:
	rm -f *.o bootloader.bin kernel.bin

cleanall:
	rm -f *.o *.bin
