[Bits 16]
global _putchar
_putchar:
	push bp
	mov  bp, sp

	mov bx, [bp+4]
	mov ah, 0x0e		; BIOS teletype output
	mov al, bl			; move ASCII value from BL to AL
	int 0x10
	
	mov sp, bp
	pop bp
	ret
