! 1 
! 1 # 1 "test.c"
! 1 # 5
! 5  
! 6 
! 7 extern void putchar();
!BCC_EOS
! 8 
! 9 int main_c()
! 10 # 9 "test.c"
! 9 {
export	_main_c
_main_c:
! 10 
! 11     putchar('X');
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const $58 (used reg = )
mov	ax,*$58
push	ax
! Debug: func () void = putchar+0 (used reg = )
call	_putchar
inc	sp
inc	sp
!BCC_EOS
! 12     return 0;
xor	ax,ax
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 13 }
! 14 
.data
.bss

! 0 errors detected
