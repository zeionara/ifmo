STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
	number db 8 DUP (?)
	fname db "L:\src.bin"
	err1msg db "Error with opening file$"
	err2msg db "Error with reading file$"

	;

	; Rezult after converting
	numberhex db 10 DUP (?)
	;numberhex db "HelloWorld"
	hexnum db 10 DUP (?)
	hxnm dd ?
	flag db 0

	succ db "Done! There is result: $"
	err db "An error occured. Please, check input data.$"

	position dw 20
	fdname db "L:\dest.txt"

DATA ENDS

EXTRN readnumber : FAR, convert : FAR, writenumber : FAR

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
		;int 21h

		;
		; Converting
		;

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

		;
		; Outputing to file
		;

	push offset numberhex
	push position
	push offset fdname

	call writenumber

    ; Returning control to OS
    toexit:
	MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
