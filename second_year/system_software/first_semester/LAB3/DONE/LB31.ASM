

PUBLIC convert

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE
	convert PROC FAR
		.386
	;push ax
	;push ax
	pushad
	mov bp, sp
	add sp, 36
		
	xor edx, edx
	xor eax, eax
	xor edi, edi
	xor esi, esi

	pop bx

	lp0_:
		cmp [bx + si], 36
		je exlp0_
		inc si
		jmp lp0_
	exlp0_:

	;pop si
	cmp si, 8
	jg erroroccured

		; Place for length

		mov dl, [bx + di]
		inc di
		cmp dl, 45
		jne positive_
			push 1
			jmp beginning_
		positive_:
			push 0
			cmp dl, 48
			jl erroroccured
			cmp dl, 57
			jg erroroccured

			sub dl, 48
			mov al, dl
		beginning_:
		dec si

		lp1_a:
			mov dl, [bx + di]
			inc di
				cmp dl, 48
				jl erroroccured
				cmp dl, 57
				jg erroroccured
			sub dl, 48
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

		pop dx
		cmp dx, 1
		jne cop
			not eax
			inc eax
		cop:
		mov [bp - 4], eax	

		mov sp, bp
		popad
		mov ax, 0

		RET

		erroroccured:
		mov sp, bp
		popad
		mov ax, 1
		RET
	convert ENDP
START:
	
	
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H

	
CODE ENDS
END START
