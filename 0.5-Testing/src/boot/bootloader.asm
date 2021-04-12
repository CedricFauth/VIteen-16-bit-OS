
;-----------------------------------------------
;        VIteen OS v0.4 by Cedric Fauth
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
	call printstr		; print boot message

	call see_segments	; print all segment addresses

	mov ax, msg_lddsk
	call printstr

	mov ax, 2
	mov bx, 0x400		; es:bx = 0x7c00+0x400 = 0x8000
	call disk_load

	; print values of loaded sectors
	; way 1 : changing es
	mov ax, 0x800			; set es to addr of first sector loaded
	mov es, ax				; ...
	call 0x800:0x0			; getting value at es+0

	mov bp, 0x7c00		; set base pointer to 0x7c00
	mov ax, 0x7c0		; store 0x7c0 temporarily
	mov ds, ax			; data segment: 0x7c0 (*0x10 when addressing)
	mov es, ax			; extra segment: 0x7c0 (*0x10 when addressing)

	xor ax,ax			; store 0 temporarily
	mov ss, ax			; set ss base to 0x0
	mov sp, bp			; set stack pointer to 0x7c00


	mov ax, msg_shutdown
	call printstr

	JMP $				; endless loop

; includes

%include 'io.asm'
%include 'log.asm'

; data labels

msg_btldr db 0xa,0xd,'[+] Bootloader started',0xa,0xd,0x0
msg_lddsk db '[+] Loading kernel from disk ...',0xa,0xd,0x0

msg_shutdown db 0xa,0xd,'[+] Jumped back',0xa,0xd,0x0

TIMES 510-($-$$) db 0x0	; padding: 2 bytes left

DW 0xaa55				; 2 byte magic number
