STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
	number db 8 DUP (?)
	fname db "L:\file.txt"
	err1msg db "Error with opening file$"
	err2msg db "Error with reading file$"
DATA ENDS

EXTRN readnumber : FAR

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    ; Loading DS
    MOV AX, DATA
    MOV DS, AX
	.386

	push offset fname

	call readnumber

	mov bp, sp
		sub bp, 70
		xor si,si
		saving:
			mov ax, [bp]
			cmp al, 0
			jle exitsaving
			mov number[si],al
			inc si

			shr ax, 8

			cmp al, 0
			jle exitsaving
			mov number[si],al
			inc si
			add bp,2

			jmp saving
		exitsaving:
		mov number[si],36

		xor ax,ax
		mov ah,09h
		mov dx,offset number
		int 21h


    ; Returning control to OS
    toexit:
	MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
