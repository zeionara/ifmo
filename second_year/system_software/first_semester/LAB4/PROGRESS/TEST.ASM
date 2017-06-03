STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    succ db "Done! There is result: $"
	err db "An error occured. Please, check input data.$"
	
	; Source number for converting
	number db "65536$"
	name db "L:\file.txt"

	; Rezult after converting
	numberhex db 10 DUP (?)
	hexnum db 10 DUP (?)
	hxnm dd ?
	flag db 0
DATA ENDS

EXTRN convert : FAR

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    ; Loading DS
    MOV AX, DATA
    MOV DS, AX
	.386
	
	push offset number

	pop dx

	mov ah,3Dh
    xor al,al
    xor cx,cx
    int 21h		; opening file...

    jc err1

	mov bx,ax
    mov ah,3Fh
	mov dx,offset buffer
    mov cx,8
    int 21h		; reading from file...

    jc err2
	
	err1:
	err2:
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
