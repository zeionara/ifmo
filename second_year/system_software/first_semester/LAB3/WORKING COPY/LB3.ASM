STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    succ db "Done! There is result: $"
	err db "An error occured. Please, check input data.$"
	
	; Source number for converting
	number db "911d1111$"

	; Rezult after converting
	numberhex db 10 DUP (?)
	hexnum db 10 DUP (?)
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
	
	xor si, si

	lp0_:
		cmp number[si], 36
		je exlp0_
		inc si
		jmp lp0_
	exlp0_:

	mov di, si
	dec si

	lp1_:
		xor ax,ax
		mov al, number[si]
		push ax
		dec si
		cmp si, 0
		jl exlp1_
		jmp lp1_
	exlp1_:
	cmp al, 45
	jne cc
		mov flag, 1

	cc:
	push di
	CALL convert
	cmp ax, 0
	jne goodexit
		mov ah, 9
		lea dx, err
		int 21h
		jmp toexit
	goodexit:

	mov ah, 9
	lea dx, succ
	int 21h

	mov bp, sp
	sub sp, 22

	xor di, di
	pop si
	inc si
	sub sp, si
	sub sp, si
	mov cx, si

	dec cx
	cmp flag, 1
	jne lp_writing
		dec cx
		mov numberhex[di], 45
		inc di
	
	lp_writing:
		pop ax
		mov numberhex[di], al
		inc di
		loop lp_writing
	
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
