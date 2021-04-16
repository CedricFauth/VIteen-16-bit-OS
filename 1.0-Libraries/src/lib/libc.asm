bits 16

; global accessible functions
global imodu
global _cga_setcell
global _cga_getcell
global _outb
global _inb
global _cga_moveup
global _register_irq
global _debug_segments
global _config_keyboard
global _stopping
global _sleep

extern _scr_d	; used for debug print
extern _printx
extern _prints
extern _irq	; extern interrupt request function

imodu: ;bcc function for modulo
	push bx
	xor	dx,dx
	div	bx
	mov	ax,dx
	pop bx
	ret

cs_str db 'cs: ',0x0
ds_str db 0xa,'ds: ',0x0
ss_str db 0xa,'ss: ',0x0
es_str db 0xa,'es: ',0x0
bp_str db 0xa,'bp: ',0x0
sp_str db 0xa,'sp: ',0x0

_debug_segments:
	push bp
	mov bp, sp
	
	;print cs
	push _scr_d
	push cs_str
	call _prints
	add sp, BYTE 4
	push _scr_d
	push cs
	call _printx
	add sp, BYTE 4
	;print ds
	push _scr_d
	push ds_str
	call _prints
	add sp, BYTE 4
	push _scr_d
	push ds
	call _printx
	add sp, BYTE 4
	;print ss
	push _scr_d
	push ss_str
	call _prints
	add sp, BYTE 4
	push _scr_d
	push ss
	call _printx
	add sp, BYTE 4
	;print es
	push _scr_d
	push es_str
	call _prints
	add sp, BYTE 4
	push _scr_d
	push es
	call _printx
	add sp, BYTE 4
	;print bp
	push _scr_d
	push bp_str
	call _prints
	add sp, BYTE 4
	push _scr_d
	push bp
	call _printx
	add sp, BYTE 4
	;print sp
	push _scr_d
	push sp_str
	call _prints
	add sp, BYTE 4
	mov ax, sp
	push _scr_d
	push ax
	call _printx
	add sp, BYTE 4
	
	mov sp, bp
	pop bp
	ret

_stopping:
	hlt
	ret

_sleep:
	hlt
	jmp _sleep

_register_irq:
	push bp
	mov bp, sp

	pusha
	push es
	mov ax,0x0
	mov es,ax
	cli
	mov [es:4*9], word irq_wrapper
	mov [es:4*9+2], cs
	sti
	pop es
	popa

	mov sp, bp
	pop bp
	ret

irq_wrapper:
	cli
	push bp
	mov bp, sp
	;pusha

	;wait_for_input:
	;in al, 0x64
	;and al, 0x1
	;jz  wait_for_input

	;in al, 60h
	
	;and ax, 0xFF
	;push ax
	call _irq
	;add sp, BYTE 2

	;mov al, 20h
	;out 20h, al	; enable new interrupts

	;popa
	mov sp, bp
	pop bp
	sti
	iret

_config_keyboard:	
	push bp
	mov bp, sp
	pusha

	; enable keyboard
	; clear output buffer
	wait4:
	in al, 0x64
	and al, 0x1		; test if output is full
	jz exit0
	in al, 0x60
	jmp wait4
	exit0:
	; wait for input buffer to be free
	in al, 0x64
	and al, 0x2
	jnz exit0
	mov al, 0xF4
	out 0x60, al

	;;;; dont know if this is necessary:

	; set scancode set to 1
;	wait0:
;	in  al, 0x64    ; Read Status byte
;    and al, 0x2    	; Test if input buff is ready
;    jnz wait0	    ; Wait until 1b
;	mov al, 0xF0
;	out 0x60, al	; send scancode cmd
;	wait1:
;	in al, 0x64
;	and al, 0x1		; test if output is full
;	jz wait1
;	in al, 0x60		; read output
;	cmp al, 0xFA
;	jne wait0		; if not ACK resend
;	wait2:
;	in  al, 0x64
;    and al, 0x2    	; Test if input buff is ready
;    jnz wait2	    ; Wait until 1b
;	mov al, 0x2
;	out 0x60, al	; send scancode cmd
;	wait3:
;	in al, 0x64
;	and al, 0x1		; test if output is full
;	jz wait3
;	in al, 0x60		; read scancode-set value
;	cmp al, 0xFA
;	jne wait0

	; clear output buffer
	wait5:
	in al, 0x64
	and al, 0x1		; test if output is full
	jz exit1
	in al, 0x60
	jmp wait5
	exit1:

	popa
	mov sp, bp
	pop bp
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

_cga_getcell:
	push bp
	mov bp, sp
	pushf
	push di
	push bx
	push es

	mov ax, 0xB800
	mov es, ax
	
	mov di, [bp+4]
	shl di, 1
	mov ax, [es:di]

	pop es
	pop bx
	pop di
	popf
	mov sp, bp
	pop bp
	ret

_inb:
	push bp
	mov  bp, sp
	pushf
	push dx

	mov dx, [bp+4]
	in al, dx

	pop dx
	popf
	mov sp, bp
	pop bp
	ret

_outb:
	push bp
	mov  bp, sp
	pushf
	push ax
	push dx

	mov dx, [bp+4]
	mov al, [bp+6]
 
	out dx, al
 
	pop dx
	pop ax
	popf
	mov sp, bp
	pop bp
	ret
