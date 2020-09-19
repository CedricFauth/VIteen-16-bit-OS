println:
	push ax
	mov ah, 0x0e		; BIOS teletype output
	mov al, 0xa
	int 0x10
	mov al, 0xd
	int 0x10
	pop ax
	ret

printstr:				; params: AX: string address
	
	push ax
	push si

	mov si, ax
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
		ret

printhex:				; params: AX: integer value
	
	push ax
	push bx
	push cs
	push di

	mov di, hexbuff+0x2
    mov bx, ax
    xor dx, dx
    mov cx, 0x4
	.hexloop:
		rol bx, 0x4
		mov ax, bx
		and ax, 0x0f
		cmp ax, 0x0a
		jl .cont
		add ax, 0x27
	.cont:
		add ax, 0x30
		stosb
		dec cx
		jnz .hexloop
	.exit:
		pop di
		pop cx
		pop bx
		mov ax, hexbuff
		call printstr
		pop ax
		ret

hexbuff db '0x0000',0

;testfun:
;	push bp
;	mov bp, sp
;	mov bx, [bp+0x4]
;
;	mov ah, 0x0e		; BIOS teletype output
;	mov al, bl			; move ASCII value from BL to AL
;	int 0x10
;	
;	mov sp, bp
;	pop bp
;	ret
;