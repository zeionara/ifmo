.386
.model flat, stdcall

option casemap:none
include D:\Applications\masm32\include\windows.inc
include D:\Applications\masm32\include\user32.inc
include D:\Applications\masm32\include\kernel32.inc
include D:\Applications\masm32\include\gdi32.inc

includelib D:\Applications\masm32\lib\user32.lib
includelib D:\Applications\masm32\lib\kernel32.lib
includelib D:\Applications\masm32\lib\gdi32.lib

.data
	src_msg db "Original string and mask:",0Ah
  stri db "akksdlfkdls;dke84 dj 5jgkfoqwertyuiRUop hfk*DF dfksleofdjekf98JD",0Ah
  msk_msg db 64 DUP(?),0Ah
	rez1_msg db "First result:",0Ah
  stri1 db 64 DUP (48),0Ah
	rez2_msg db "Second result:",0Ah
  stri2 db 64 DUP (48),0Ah,0

	first db 'R'
	second db 'U'
	flag db 0
  appName db "Second lab",0
	msk_o dq 0FEDCBA9876543210h


	msk_l dd 0FFFFF000h
	msk_h dd 0000FFFFFh
  FontName db "Courier New",0
  hFont dd ?
.code
  start:
	 xor esi,esi
	 xor edi,edi
	 mov ecx,64

	 mov ebx, offset msk_o
	 mov eax,[ebx + esi]
	 mov msk_l, eax
	 add esi,4
	 mov eax,[ebx + esi]
	 mov msk_h, eax

	 XOR esi,esi

	 lp0:
		clc
		rcr msk_h, 1
		rcr msk_l, 1
		JNC zeroinmask
		oneinmask:
			mov msk_msg[esi], 49
			jmp end_of_lp0
		zeroinmask:
			mov msk_msg[esi], 48
		end_of_lp0:
			add esi,1
	 loop lp0

	 xor esi,esi
	 xor edi,edi
	 mov ecx,64

	 mov ebx, offset msk_o
	 mov eax,[ebx + esi]
	 mov msk_l, eax
	 add esi,4
	 mov eax,[ebx + esi]
	 mov msk_h, eax

	 xor esi,esi

	 lp1:
		clc
		rcr msk_h, 1
		rcr msk_l, 1
		jnc end_of_lp1
			mov al, stri[esi]
				cmp al,97
				jl end_of_lp1
				cmp al,122
				jg end_of_lp1
			mov stri1[edi],al
			add edi,1
			end_of_lp1:
			add esi,1
    loop lp1

  mov cx,64
	mov esi,63
	xor di,di
	lp2:
	 mov al,stri[si]
	 cmp flag,1
	 je if_R_break
	 jmp cont2
	 if_R_break:
	  cmp first, al
		mov stri2[di],al
		je exit_lp2
	  cont2:
		  cmp second, al
			je setflag
			jmp cont1
			setflag:
			   mov flag,1
			cont1:
			   mov stri2[di],al
				 add di,1
		end_of_lp2:
	  dec si
  loop lp2
  exit_lp2:

	cmp cx,0
	je afterlp2
		DEC di
		mov stri2[di],0Ah
		INC di
		mov stri2[di],0
	afterlp2:

	; Outputing

  invoke MessageBox,NULL,addr src_msg,addr appName,MB_OK
end start
