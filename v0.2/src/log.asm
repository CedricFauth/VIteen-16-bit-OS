; prints all absolute segment locations
see_segments:               ; params: none
    push ax
    ; info message
    mov ax, seg_string
    call printstr

    ; example for addr of cs (code segment) 
    mov ax, cs_string       ; addr of 'cs at...' in ax
    call printstr           ; print message
    ; now printing the actual address
    mov ax, cs              ; addr of cs in ax
    shl ax, 0x4             ; ax * 16 = absolute address
	call printhex           ; print number in ax

    mov ax, ds_string
    call printstr
	mov ax, ds
    shl ax, 0x4
	call printhex

    mov ax, ss_string
    call printstr
	mov ax, ss
    shl ax, 0x4
	call printhex

    mov ax, es_string
    call printstr
	mov ax, es
    shl ax, 0x4
	call printhex
	call println
    ; return
    pop ax
    ret

; message buffers
seg_string db '[+] Segments initialized',0x0
cs_string db 0xa,0xd,'  CS at ',0x0
ds_string db 0xa,0xd,'  DS at ',0x0
ss_string db 0xa,0xd,'  SS at ',0x0
es_string db 0xa,0xd,'  ES at ',0x0

