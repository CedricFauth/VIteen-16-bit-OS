[Bits 16]
global _putchar2
global _putchar
global _printstr

_putchar2:
	push bp
	mov bp, sp
	push ax
	push bx

	mov bx, [bp+4]

	push es
	mov ax, 0xB800
	mov es, ax
	mov [es:0x2], bx
	pop ax
	mov es, ax

	pop bx
	pop ax
	mov sp, bp
	pop bp
	ret

; printing a string
_printstr:				; params: AX: string address
	
	push bp
	mov  bp, sp

	mov si, [bp+4]

	push ax
	push si

	;mov si, ax
	mov ah, 0x0e		; BIOS teletype output
	.printloop:
		lodsb			; al = *(si++)
		or al, al			
		jz .exit		; check if al is 0 byte
		int 0x10		; print value of al
		jmp .printloop	; jump up for next letter
	.exit:
		pop si
		pop ax

		mov sp, bp
		pop bp
		ret

_putchar:
	push bp
	mov  bp, sp
	push ax
	push bx

	mov bx, [bp+4]
	mov ah, 0x0e		; BIOS teletype output
	mov al, bl			; move ASCII value from BL to AL
	int 0x10
	
	pop bx
	pop ax
	mov sp, bp
	pop bp
	ret
