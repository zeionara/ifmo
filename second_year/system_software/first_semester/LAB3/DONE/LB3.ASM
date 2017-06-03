STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    succ db "Done! There is result: $"
	err db "An error occured. Please, check input data.$"
	
	; Source number for converting
	number db "65536$"

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

	CALL convert

	cmp ax, 0
	je goodexit
		mov ah, 9
		lea dx, err
		int 21h
		jmp toexit
	goodexit:

	mov ah, 9
	lea dx, succ
	int 21h

	sub sp, 40

	pop edx
	mov hxnm, edx
	
	mov si, 8
	xor di, di
	lpcopy:
		rol edx, 4

		xor cl, cl
		mov cl, dl
		
		shl cl, 4
		clc
		rcr cl, 1
		shr cl, 3
		
		cmp cl, 9
		jg addmore
			add cl, 48
			jmp contee
		addmore:
			add cl, 55
		contee:
		mov numberhex[di], cl
		inc di
		
		dec si
		cmp si, 0
		jle exlpcopy
		jmp lpcopy
	
	exlpcopy:
	mov numberhex[di], 36
	
	mov ah, 9
	lea dx, numberhex
	int 21h

	toexit:
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
