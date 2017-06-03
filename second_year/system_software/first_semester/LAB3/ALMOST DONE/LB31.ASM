STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

PUBLIC convert

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, SS:STACK
	convert PROC FAR
		.386
		pusha
		mov bp, sp
		mov bx, bp
		add sp, 20
		
		xor edx, edx
		xor eax, eax
		xor edi, edi
		xor esi, esi

		pop ax
		pop ax
		pop ax
		add ax, 48
		int 29h

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
START:
	
	
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H

	
CODE ENDS
END START
