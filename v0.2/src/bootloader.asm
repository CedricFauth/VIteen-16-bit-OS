
;-----------------------------------------------
;        VIteen OS v0.2 by Cedric Fauth
;-----------------------------------------------

; setting up directives for nasm

bits 16				; only 16 bit support
org 0x0000			; base adress in memory


jmp 0x7c0:entry			; far jump to entry (0x7c0 * 0x10 + entry)
						; ... 0x7c00 to setup cs properly

; boot loader's entry point

entry:

	mov bp, 0x7c00		; set base pointer to 0x7c00
	mov ax, 0x7c0		; store 0x7c0 temporarily
	mov ds, ax			; data segment: 0x7c0 (*0x10 when addressing)
	mov es, ax			; extra segment: 0x7c0 (*0x10 when addressing)

	xor ax,ax			; store 0 temporarily
	mov ss, ax			; set ss base to 0x0
	mov sp, bp			; set stack pointer to 0x7c00

	mov ax, msg_btldr	; load first address of message
	call printstr		; print message
	mov ax, msg_sgmts
	call printstr

	mov ax, 0xface
	call printhex
	call println

	mov ax, ds
	call printhex
	call println

	mov ax, 0x1a3b
	call printhex
	call println

	mov ax, 12
	call printhex
	call println

	JMP $				; endless loop

; data labels

msg_btldr db 0xa,0xd,'[+] Bootloader started',0xa,0xd,0x0
msg_sgmts db '[+] Segments initialized',0xa,0xd,0x0

%include 'io.asm'

TIMES 510-($-$$) db 0	; padding: 2 bytes left

DW 0xaa55				; 2 byte magic number

