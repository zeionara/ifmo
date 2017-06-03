STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    succ db "Done! There is result: $"
	err db "An error occured. Please, check input data.$"
	
	number db "+1111111$"
	numberhex db 10 DUP (?)
	hexnum db 10 DUP (?)
	flag db 0
DATA ENDS

;EXTRN convert : FAR

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

	convert PROC
		.386
		;push ax
	push ax
	pusha
	mov bp, sp
	mov bx, bp
	add sp, 20
		
	xor edx, edx
	xor eax, eax
	xor edi, edi
	xor esi, esi

	pop si
	cmp si, 8
	jg erroroccured

		; Place for length
		sub bp, 2

		pop dx
		cmp dx, 45
		jne positive_
			sub bp, 2
			mov [bp], dx
			jmp beginning_
		positive_:
			cmp dx, 48
			jl erroroccured
			cmp dx, 57
			jg erroroccured

			sub dx, 48
			mov ax, dx
		beginning_:
		dec si


		lp1_a:
			pop dx
				cmp dx, 48
				jl erroroccured
				cmp dx, 57
				jg erroroccured
			sub dx, 48
			dec si
			mov ecx, eax
			shl eax, 3
			add eax, ecx
			add eax, ecx
			add eax, edx

			cmp si, 0
			jle exlp1_a
			jmp lp1_a
		exlp1_a:

		

		lp2_a:
			cmp eax, 16
			jl exlp2_a
			xor esi, esi
			lp3_a:
				sub eax, 16
				inc esi
				cmp eax, 16
				jge lp3_a
			mov dx, ax
			mov eax, esi
			
			cmp dx, 9
			jg addmore_a
				add dx, 48
				jmp cont2_a
			addmore_a:
				add dx, 55
			cont2_a:
				sub bp, 2
				mov [bp], dx
			jmp lp2_a
		exlp2_a:

		mov edx, eax
			cmp dx, 9
			jg addmore1_a
				add dx, 48
				jmp cont3_a
			addmore1_a:
				add dx, 55
			cont3_a:

		sub bp, 2
		mov [bp], dx	

		mov ax, bx
		sub ax, bp
		sub ax, 2
		shr ax, 1

		mov bp, bx
		mov [bp - 2], ax
		mov ax, 1

		mov sp, bp
		popa
		pop ax
		mov ax, 1
		;pop ax
		RET

		erroroccured:
		mov ax, 0
		mov bp, bx
		mov sp, bp
		popa
		pop ax
		mov ax, 0
		;pop ax
		RET
	convert ENDP
CODE ENDS
END START
