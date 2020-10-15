bits 16
extern _main_c   ; _main_c declaration
global _main

_main:
    mov ax, cs      ; get cs address
    mov ds, ax      ; set data segment
    mov ss, ax      ; set stack segment

    mov ax, 0xFFFF  ; set stackpointer
    mov sp, ax
    call _main_c     ; call _main_c
    
    cli
    hlt

