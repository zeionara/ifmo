STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    ; Original string
	stri1 db 64 DUP (0)
	gg db "-end-"
	stri2 db 64 DUP (0)
	gg1 db "-end-"
	stri db "akksdlfkdls;dke84 dj 5jgkfoqwertyuiRUop hfk*DF dfksleofdjekf98JD"
	first db 'R'
	second db 'U'
	flag db 0

	msk_lo dd 0FFFFFFFFh
	msk_ho dd 0FFFFFFFFh


	; Mask for original string
	msk_l dd 0FFFFFFFFh
	msk_h dd 0FFFFFFFFh
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
	;LEA bx,msk
	;MOV edx,dword ptr [bx + 8]
	; Now in dx the dx the greatest values from mask

	MOV eax, msk_lo
	MOV msk_l, eax
	MOV eax, msk_ho
	MOV msk_h, eax

	; Working with string, using mask
	lp1:
		; if bit in mask = 0 then do nothing
		;mov eax, msk_h
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

    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
