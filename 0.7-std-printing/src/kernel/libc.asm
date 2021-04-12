bits 16

global _cga_setchar
global _outb
global imodu

imodu: ;bcc function for modulo
	push bx
	xor	dx,dx
	div	bx
	mov	ax,dx
	pop bx
	ret

_cga_setchar:
	push bp
	mov bp, sp
	pushf
	push ax
	push bx
	push es

	mov ax, 0xB800
	mov es, ax
	
	mov ax, [bp+4]
	mov di, [bp+6]
	shl di, 1
	mov [es:di], ax

	pop ax
	mov es, ax
	pop bx
	pop ax
	popf
	mov sp, bp
	pop bp
	ret

_outb:
	push bp
	mov  bp, sp
	pushf
	push eax
	push edx

	mov dx, [bp+4]
	mov al, [bp+6]
 
	out dx, al
 
	pop edx
	pop eax
	popf
	mov sp, bp
	pop bp
	ret
