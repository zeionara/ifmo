

PUBLIC readnumber, writenumber

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE
	readnumber PROC FAR
		.386
	;push ax
	;push ax
	pushad
	push ds
	
	mov bp, sp
	;add bp, 38
		
	;xor edx, edx
	;xor eax, eax
	;xor edi, edi
	;xor esi, esi

	mov dx, [bp + 38]
	;sub sp, 40

	mov ah,3Dh
    xor al,al
    xor cx,cx
    int 21h		; opening file...

    jc err1

	mov bx,ax
    mov ah,3Fh
	push ss
	pop ds
	mov dx,bp
	sub dx, 32
    mov cx,8
    int 21h		; reading from file...

    jc err2

	mov ah,3Eh
    xor al,al
    xor cx,cx
    int 21h		; closing file...


	jmp toexitnormal

	err1:
		jmp toexiterr
	err2:
		jmp toexiterr

		toexiterr:
		mov sp, bp
		pop ds
		popad
		mov ax, 1
		RET
		

		toexitnormal:
		mov sp, bp
		pop ds
		popad
		mov ax, 0
		RET
	readnumber ENDP

	writenumber PROC FAR
		.386
	;push ax
	;push ax
	pushad
	push ds
	
	mov bp, sp
	;add bp, 38
		
	;xor edx, edx
	;xor eax, eax
	;xor edi, edi
	;xor esi, esi

	mov dx, [bp + 38]
	;sub sp, 40

	mov ah,3Dh
    mov al, 2
    xor cx,cx
    int 21h		; opening file...

    jc err1a

	mov bx, ax
	mov ah, 42h
	mov dx, [bp + 40]
	xor cx, cx
	xor al, al
	int 21h		; positioning in file...
	
	;jc err1a
	
	;mov bx,ax               ;Дескриптор файла
    xor ah,ah
	mov ah,40h              ;Функция DOS 40h (запись в файл)
    mov dx,[bp + 42]        ;Адрес буфера с данными
    mov cx,8         ;Размер данных
    int 21h

    jc err2a

	mov ah,3Eh
    xor al,al
    xor cx,cx
    int 21h		; closing file...

	jc err2a

	jmp toexitnormal

	err1a:
		jmp toexiterra
	err2a:
		jmp toexiterra

		toexiterra:
		mov sp, bp
		pop ds
		popad
		mov ax, 1
		RET
		

		toexitnormala:
		mov sp, bp
		pop ds
		popad
		mov ax, 0
		RET
	writenumber ENDP

    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H

	
CODE ENDS
END