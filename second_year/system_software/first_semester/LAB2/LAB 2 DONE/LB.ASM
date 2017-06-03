STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    ; Messages
	src_msg db "Original string and mask:",0Ah,'$'
	rez1_msg db "First result:",0Ah,'$'
	rez2_msg db "Second result:",0Ah,'$'
	

	stri1 db 64 DUP (0),0Ah,'$'
	
	stri2 db 64 DUP (0),0Ah,'$'
	
	stri db "akksdlfkdls;dke84 dj 5jgkfoqwertyuiRUop hfk*DF dfksleofdjekf98JD",0Ah,'$'
	
	first db 'R'
	second db 'U'
	flag db 0

	; Mask for original string
	msk_o dq 0FEDCBA9876543210h
	; msk_ho dd 0FFF1FFF1h
	msk_msg db 64 DUP(?),0Ah,'$'

	msk_l dd 0FFFFF000h
	msk_h dd 0000FFFFFh
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    ; Loading DS
    MOV AX, DATA
    MOV DS, AX
	.386

	;Preparing to work cycle
	XOR si,si
	XOR di,di
	MOV cx,64

	MOV bx, offset msk_o
	MOV eax,[bx + si]
	MOV msk_l, eax
	ADD si,4
	MOV eax,[bx + si]
	MOV msk_h, eax

	XOR si,si

	; Creating string representation of mask
	lp0:
		; if bit in mask = 0 then do nothing
		;mov eax, msk_h
		clc
		rcr msk_h, 1
		rcr msk_l, 1
		JNC zeroinmask
		oneinmask:
			mov msk_msg[si], 49
			JMP endoflp0
		zeroinmask:
			mov msk_msg[si], 48
		endoflp0:
			add si,1
	loop lp0

	XOR si,si
	XOR di,di
	MOV cx,64

	;MOV eax, msk_lo
	;MOV msk_l, eax
	;MOV eax, msk_ho
	;MOV msk_h, eax

	MOV bx, offset msk_o
	MOV eax,[bx + si]
	MOV msk_l, eax
	ADD si,4
	MOV eax,[bx + si]
	MOV msk_h, eax

	XOR si,si

	; Working with string, using mask
	lp1:
		; if bit in mask = 0 then do nothing
		clc
		rcr msk_h, 1
		rcr msk_l, 1
		JNC endoflp1
		; else check, are we should move symbol to str1
			MOV al, stri[si]
				CMP al,97
				JL endoflp1
				CMP al,122
				JG endoflp1
			MOV stri1[di],al
			ADD di,1
			endoflp1:
			ADD si,1
    loop lp1

	MOV cx,64
	MOV si,63
	XOR di,di
	; Working with string, using mask
	lp2:

		; check, are we should move symbol to str2
			MOV al,stri[si]
			CMP flag,1
			JE ifRbreak
			JMP cont2
			ifRbreak:
				CMP first, al
				MOV stri2[di],al
				JE exitlp2
			cont2:
				CMP second, al
				JE setflag
				JMP cont1
				setflag:
					MOV flag,1
				cont1:
					MOV stri2[di],al
					ADD di,1
			endoflp2:
			DEC si
    loop lp2
    exitlp2:
	cmp cx,0
	JE afterlp2
		DEC di
		mov stri2[di],0Ah
		INC di
		mov stri2[di],36
	afterlp2:
	
	; Outputing
	mov ah,9
	mov dx,offset src_msg
	int 21h
	
	mov ah,9
	mov dx,offset stri
	int 21h

	mov ah,9
	mov dx, offset msk_msg
	int 21h

	mov ah,9
	mov dx, offset rez1_msg
	int 21h
	
	mov ah,9
	mov dx, offset stri1
	int 21h

	mov ah,9
	mov dx, offset rez2_msg
	int 21h

	mov ah,9
	mov dx, offset stri2
	int 21h
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
