STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP (?)
STACK ENDS
DATA SEGMENT PARA PUBLIC 'data'
    mas dw 1,2,-3,43,-22,23,734,34,-6,3,44,2,22
    mas1 dw 13 DUP (?)
DATA ENDS
CODE SEGMENT PARA PUBLIC 'code'
    assume cs:CODE, ds:DATA, ss:STACK
START:
   mov ax, DATA
   mov ds,ax

   xor si,si
   xor di,di
   mov cx, 13
   loop1:
     dec cx
     mov bx, mas
     mov ax, [bx+si]
     add si,2

     cmp ax,0
     jl lessthanzero
     jmp morethanzero

     lessthanzero:
     mov bx, mas1
     mov [bx+di], ax
     add di,2
     loop loop1

     morethanzero:
     loop loop1

     mov ax, 4C00H
     int 21h
CODE ENDS
END START
