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
		
		xor dx, dx
		xor ax, ax
		xor di, di
		xor si, si
		mov cl, 10
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
			mov ax,dx
		beginning:

		lp1:
			pop dx
				cmp dx, 48
				jl exlp1
				cmp dx, 57
				jg exlp1
				sub dl, 48
			dec si
			
			mul cl
			add ax, dx
			cmp ax, 16
			jl continuecycle
			xor di, di
			lp2:
				sub ax, 16
				inc di
				cmp ax, 16
				jl endoflp2
				jmp lp2
			endoflp2:
			cmp di, 9
			jg addmore
				add di, 48
				jmp nextact
			addmore:
				sub di, 10
				add di, 65
			nextact:
				sub bp, 2
				mov [bp], di
			continuecycle:
				cmp si, 0
				jle exlp1
			endoflp1:
		jmp lp1

		exlp1:
		cmp ax, 9
		jg addmore1
			add ax, 48
			jmp nextact1
		addmore1:
			sub ax, 10
			add ax, 65
		nextact1:
			sub bp, 2
			mov [bp], ax

		mov ax, bx
		sub ax, bp
		sub ax, 2
		shr ax, 1
		add ax, 48
		int 29h
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
