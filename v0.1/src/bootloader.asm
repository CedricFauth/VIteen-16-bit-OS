
;-----------------------------------------------
;        VIteen OS v0.1 by Cedric Fauth
;-----------------------------------------------

; setting up directives for nasm

bits 16				; only 16 bit support
org 0x7c00			; base adress in memory


jmp 0x00:entry			; far jump into entry point
				; ... to setup cs properly
; boot loader's entry point

entry:
 
    cli
    xor ax, ax			; ax = 0
    mov ds, ax			; data segment = base + 0
    mov ss, ax			; stack segment = base + 0
    mov es, ax			; extra segment = base + 0

    mov bp, 0x7c00		; set base pointer under boot code
    mov sp, bp			; set stack pointer = base pointer
    sti

    ; print letter A via BIOS int

    push 'A'
    mov ah, 0x0e
    pop bx
    mov al, bl
    int 10h

    JMP $			; endless loop

TIMES 510-($-$$) db 0		; padding: 2 bytes left

DW 0xaa55			; 2 byte magic number

