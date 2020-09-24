
;-----------------------------------------------
;      bootloader library by Cedric Fauth
;-----------------------------------------------

; printing a new line
println:
	push ax
	mov ah, 0x0e		; BIOS teletype output
	mov al, 0xa			; '\n'
	int 0x10			; print ir
	mov al, 0xd			; '\r'
	int 0x10			; print ir
	pop ax
	ret

; printing a string
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

; printing a hex number
printhex:				; params: AX: integer value
	
	push ax
	push bx
	push cs
	push di

	mov di, hexbuff+0x2	; load buff+2 in di
    mov bx, ax			; bx stores hex value
    xor dx, dx			; dx = 0
    mov cx, 0x4			; loop counter = 4
	.hexloop:
		rol bx, 0x4		; rotate bx left 0x1234 -> 0x2341
		mov ax, bx		; ax = bx
		and ax, 0x0f	; ax = 0-4th lsb's 0x2341 -> 0x0001
		cmp ax, 0x0a	; check if ax <(less) 10
		jl .cont
		add ax, 0x27	; no: add 0x27(+0x30) to get 'a'-'f'
	.cont:
		add ax, 0x30	; default: add 0x30 to get '1'-'9'
		stosb			; *dx = ax; ++dx
		dec cx			; --counter
		jnz .hexloop	; exit if cs = 0
	.exit:
		pop di
		pop cx
		pop bx
		mov ax, hexbuff	; store buf addr in ax
		call printstr	; print buff
		pop ax
		ret

	hexbuff db '0x0000',0	; internal buffer for printing hex

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