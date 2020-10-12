ASM=nasm

all: os clean

bootloader.bin: boot/io.asm boot/log.asm boot/bootloader.asm
	$(ASM) -f bin boot/bootloader.asm -o bootloader.bin -iboot/

test.o: ctest/test.c
	bcc -ansi -0 -c -o test.o ctest/test.c
	
libc.o: ctest/libc.asm
	nasm -f as86 -o libc.o ctest/libc.asm

start.o: ctest/start.asm
	nasm -f as86 -o start.o ctest/start.asm

kernel.bin: start.o libc.o test.o
	ld86 -d -T 0x8000 -o kernel.bin start.o test.o libc.o

.PHONY: os qemu clean cleanall
os: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os.bin

qemu: os clean
	qemu-system-x86_64 -curses -drive file=os.bin,index=0,if=floppy,format=raw

clean:
	rm -f *.o bootloader.bin kernel.bin

cleanall:
	rm -f *.o *.bin
