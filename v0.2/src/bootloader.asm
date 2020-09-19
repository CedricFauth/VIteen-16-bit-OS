
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

    ; print letter A via BIOS int

    mov ah, 0x0e		; BIOS teletype output
    push 'B'			; push 'B' on stack
    push 'A'			; push 'A' on stack

    pop bx			; pop 'A'
    mov al, bl			; move ASCII value from BL to AL
    int 0x10			; raise interrupt: BIOS print routine

    mov bx, [bp-2]		; mov 'A' from stack to BX
    mov al, bl
    int 0x10

    JMP $			; endless loop

TIMES 510-($-$$) db 0		; padding: 2 bytes left

DW 0xaa55			; 2 byte magic number

