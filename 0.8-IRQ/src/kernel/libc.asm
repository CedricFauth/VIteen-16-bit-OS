bits 16

global _cga_setcell
global _outb
global _cga_moveup
global imodu

global _register_irq
global _halt

extern _irq

_halt:
	hlt
	jmp _halt

_register_irq:
	push bp
	mov bp, sp

	pusha
	mov ax,0x0
	mov es,ax
	cli
	mov [es:4*9], word irq_wrapper
	mov [es:4*9+2], cs
	sti
	popa

	mov sp, bp
	pop bp
	ret

irq_wrapper:
	pusha
	in al, 60h	; change later
	
	call _irq

	mov al, 61h	; change later
	out 20h, al	; change later
	popa
	iret


imodu: ;bcc function for modulo
	push bx
	xor	dx,dx
	div	bx
	mov	ax,dx
	pop bx
	ret

_cga_moveup:
	push bp
	mov bp, sp
	pushf
	push di
	push ax
	push bx
	push es

	mov ax, 0xB800
	mov es, ax
	
	mov di, [bp+4]
	shl di, 1
	mov ax, WORD [es:di]
	mov bx, [bp+6]
	shr di, 1
	sub di, bx
	shl di, 1
	mov [es:di], ax

	pop ax
	mov es, ax
	pop bx
	pop ax
	pop di
	popf
	mov sp, bp
	pop bp
	ret

_cga_setcell:
	push bp
	mov bp, sp
	pushf
	push di
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
	pop di
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
