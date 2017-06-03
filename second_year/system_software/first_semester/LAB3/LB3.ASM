STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    number db "256$"
	hexnum db 10 DUP (?)
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

	lp0:
		cmp number[si], 36
		je exlp0
		inc si
		jmp lp0
	exlp0:

	mov di, si
	dec si

	lp1:
		xor ax,ax
		mov al, number[si]
		push ax
		dec si
		cmp si, 0
		jl exlp1
		jmp lp1
	exlp1:

	push di
	CALL convert

	mov bp, sp
	mov ax, 22
	;sub sp, 22
	pop cx
	add ax, cx
	add ax, cx
	sub sp, ax
	dec cx
	lp3:
		pop ax
		int 29h
	loop lp3

	; in ax - length of number in hex
	;mov cx, ax
	;xor si, si

	;lp2:
	;	pop ax
	;	mov hexnum[si], al
	;	inc si
	;loop lp2

	;mov hexnum[si], 36
	
	mov sp, bp

	;mov ah,9
	;mov dx, offset hexnum
	;int 21h
	
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
