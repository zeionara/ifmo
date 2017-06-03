STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    number db "-256$"
	hexnum db 10 DUP (?)
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

	push di
	;CALL convert

	push ax
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

		; Place for length
		sub bp, 2

		pop dx
		cmp dx, 45
		jne positive_
			sub bp, 2
			mov [bp], dx
			jmp beginning_
		positive_:
			sub dx, 48
			mov ax, dx
		beginning_:
		dec si


		lp1_a:
			pop dx
				cmp dx, 48
				jl exlp1_a
				cmp dx, 57
				jg exlp1_a
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

		mov sp, bp
		popa
		pop ax
		pop ax

		mov bp, sp
		sub sp, 22

    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H

	convert PROC
		.386
		pusha
		mov bp, sp
		mov bx, bp
		add sp, 18
		
		xor edx, edx
		xor eax, eax
		xor edi, edi
		xor esi, esi

		pop ax
		pop ax
		pop ax
		;add ax, 48
		;int 29h

		mov bp, bx
		mov sp, bp
		popa
		RET

		pop si

		; Place for length
		sub bp, 2

		pop dx
		cmp dx, 45
		jne positive
			sub bp, 2
			mov [bp], dx
			jmp beginning
		positive:
			mov ax, dx
		beginning:
		add ax, 48
		int 29h
		sub ax, 48

		


		mov bp, bx
		mov sp, bp
		popa
		RET

		lp1:
			pop dx
				cmp dx, 48
				jl exlp1
				cmp dx, 57
				jg exlp1
			sub dx, 48
			dec si
			mov ecx, eax
			shl eax, 3
			add eax, ecx
			add eax, ecx
			add eax, edx

			cmp si, 0
			jl exlp1
			jmp lp1
		exlp1:

		;mov bp, bx
		;mov sp, bp
		;popa
		;RET

		lp2:
			cmp eax, 16
			jl exlp2
			xor esi, esi
			lp3:
				sub eax, 16
				inc esi
				cmp eax, 16
				jg lp3
			mov dx, ax
			mov eax, esi
			
			cmp dx, 9
			jg addmore
				add dx, 48
				jmp cont2
			addmore:
				add dx, 55
			cont2:
				sub bp, 2
				mov [bp], dx
			jmp lp2
		exlp2:
			mov edx, eax
			cmp dx, 9
			jg addmore1
				add dx, 48
				jmp cont3
			addmore1:
				add dx, 55
			cont3:
		sub bp, 2
		mov [bp], dx	

		mov ax, bx
		sub ax, bp
		sub ax, 2
		shr ax, 1

		mov bp, bx
		mov [bp - 2], ax

		mov sp, bp
		popa
		RET
	convert ENDP
CODE ENDS
END START
