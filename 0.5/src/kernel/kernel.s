! 1 
! 1 # 1 "kernel/kernel.c"
! 1 # 5
! 5  
! 6 
! 7 extern void putchar();
!BCC_EOS
! 8 extern void putchar2();
!BCC_EOS
! 9 extern void printstr();
!BCC_EOS
! 10 
! 11 char a = 'A';
.data
export	_a
_a:
.byte	$41
!BCC_EOS
! 12 char *str = "\n\rHello World!";
.blkb	1
export	_str
_str:
.word	.1+0
!BCC_EOS
! 13 
! 14 
! 15 struct cell {
! 16     char ascii:8;
!BCC_EOS
! 17     char fb:4;
!BCC_EOS
! 18     char bg:3;
!BCC_EOS
! 19     char blink:1;
!BCC_EOS
! 20 };
!BCC_EOS
! 21 
! 22 int main_c()
! 23 # 22 "kernel/kernel.c"
! 22 {
.text
export	_main_c
_main_c:
! 23 
! 24     char x = 'X';
push	bp
mov	bp,sp
push	di
push	si
dec	sp
! Debug: eq int = const $58 to char x = [S+7-7] (used reg = )
mov	al,*$58
mov	-5[bp],al
!BCC_EOS
! 25     struct cell cell1;
!BCC_EOS
! 26 
! 27     cell1.ascii = 'A';
add	sp,*-5
! Debug: eq int = const $41 to char cell1 = [S+$C-$B] (used reg = )
mov	al,*$41
mov	-9[bp],al
!BCC_EOS
! 28     cell1.fb = 	0xc;
! Debug: eq int = const $C to char cell1 = [S+$C-$A] (used reg = )
mov	al,*$C
mov	-8[bp],al
!BCC_EOS
! 29     cell1.bg = 0x3;
! Debug: eq int = const 3 to char cell1 = [S+$C-9] (used reg = )
mov	al,*3
mov	-7[bp],al
!BCC_EOS
! 30     cell1.blink = 0;
! Debug: eq int = const 0 to char cell1 = [S+$C-8] (used reg = )
xor	al,al
mov	-6[bp],al
!BCC_EOS
! 31 
! 32     putchar(a);
! Debug: list char = [a+0] (used reg = )
mov	al,[_a]
xor	ah,ah
push	ax
! Debug: func () void = putchar+0 (used reg = )
call	_putchar
inc	sp
inc	sp
!BCC_EOS
! 33     putchar(x);
! Debug: list char x = [S+$C-7] (used reg = )
mov	al,-5[bp]
xor	ah,ah
push	ax
! Debug: func () void = putchar+0 (used reg = )
call	_putchar
inc	sp
inc	sp
!BCC_EOS
! 34     printstr(str);
! Debug: list * char = [str+0] (used reg = )
push	[_str]
! Debug: func () void = printstr+0 (used reg = )
call	_printstr
inc	sp
inc	sp
!BCC_EOS
! 35 
! 36     putchar2(cell1);
! Debug: list struct cell cell1 = [S+$C-$B] (used reg = )
add	sp,*-4
mov	ax,sp
mov	ax,*4
push	ax
lea	bx,-9[bp]
push	bx
push	ax
call	_memcpy
add	sp,*6
! Debug: func () void = putchar2+0 (used reg = )
call	_putchar2
add	sp,*4
!BCC_EOS
! 37 
! 38     return 0;
xor	ax,ax
add	sp,*6
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 39 }
! 40 
! Register BX used in function main_c
.data
.1:
.2:
.byte	$A,$D
.ascii	"Hello World!"
.byte	0
.bss

! 0 errors detected
