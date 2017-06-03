

PUBLIC convert

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE
	convert PROC FAR
		.386
		;push ax
	;push ax
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
		;pop ax
		mov ax, 1
		;pop ax
		RET

		erroroccured:
		mov ax, 0
		mov bp, bx
		mov sp, bp
		popa
		;pop ax
		mov ax, 0
		;pop ax
		RET
	convert ENDP
START:
	
	
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H

	
CODE ENDS
END START
