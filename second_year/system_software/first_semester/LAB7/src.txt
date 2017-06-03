STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS


DATA SEGMENT PARA PUBLIC 'data'
    ;<<<<<<<<<<<<<<<<<<<<<<<<float_number_to_string
	int_num_of_pre_zeros dd 0
    cw_buffer dw 0
    minus db 0
	five dd 5.0
    ten dd 10.0
    ascii_m dd 49.0
    
    len_of_int dd 0
    int_buf dd 0
    float_buf dd 0

    int_tmp dd 0
    num_str db 100 DUP (32),"$"
    float_str db 100 DUP (32),"$"
    ;>>>>>>>>>>>>>>>>>>>>>>>>>float_number_to_string

	typeX0MSG db "Please, type x0 here :$"
	typeXNMSG db "Please, type xn here :$"
	typeSTEPMSG db "Please, type step here :$"
	typeACCMSG db "Please, type accuracy here :$"

    err1MSG db 0ah,"Invalid argument$"
    buffer db 256 DUP(?),'$'
    ;ten dd 10.0
    
	x dd 4.9
	fact dd 1
	minus_one dd -1.0
	plus_one dd 1.0

	previous_stupid_rezult dd 0.0
	stupid_rezult dd 0.0
	factical_accuracy dd 0.0
	required_accuracy dd 0.000001
	num_of_members dd 0

	brainy_rezult dd 0.0

	x_end dd 9.6
	x_step dd 0.3
	num_of_steps dd 0

	one dd 1.0
	u_n dw 0
    count dw 0

	new_line db 0ah,"$"
	atomic_rezult db "For the x = ","$"
	atomic_rezult1 db " e^(-x) with using function = ","$"
	atomic_rezult2 db " and with using stupid method = ","$"
	atomic_rezult3 db " and number of members = ","$"
	atomic_rezult4 db 0ah,"$"
	cur_iteration dd 0
	;atomic_rezult2 db " e^(-x) with using function = ... and with using stupid method = ... and number of members = ... ",0ah,"$"
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS: CODE, DS: DATA, SS: STACK
    .386
    START: MOV AX, DATA
    MOV DS, AX
    
	;
	;getting data
	;
	mov ah,09h
	mov dx, offset typeX0MSG
	int 21h

	CALL read_to_st
	fstp x

	mov ah,09h
	mov dx, offset new_line
	int 21h

	mov ah,09h
	mov dx, offset typeXNMSG
	int 21h
	
	CALL read_to_st
	fstp x_end

	mov ah,09h
	mov dx, offset new_line
	int 21h

	mov ah,09h
	mov dx, offset typeSTEPMSG
	int 21h

	CALL read_to_st
	fstp x_step

	mov ah,09h
	mov dx, offset new_line
	int 21h

	mov ah,09h
	mov dx, offset typeACCMSG
	int 21h

	CALL read_to_st
	fstp required_accuracy

	mov ah,09h
	mov dx, offset new_line
	int 21h

	;CALL read_to_st


	;
	;counting
	;

	CALL load_stepnum_to_cx
	lp_brainy:
		
    		

		;init
		mov cur_iteration,esi
		fldz
		fst previous_stupid_rezult
		fst stupid_rezult
		fst factical_accuracy
		;brainy part
		CALL e_to_minus_x
		;end of brainy part
		;
		;begin of stupid part
		push cx
		mov cx, 100
		xor si, si
		lp1:
			push cx
			mov cx, si
			CALL addMember
			pop cx
			inc si

			CALL set_accuracy
			CALL save_previous_stupid_rezult
		loop lp1
		countedMember:
			fild num_of_members
			fld factical_accuracy
			fld stupid_rezult
		;end of stupid part
		CALL move_to_next_x

		CALL show_atomic_rezult
		pop cx
		pop cx
	loop lp_brainy
	
    ;
    MOV AX, 4C00H
    INT 21H

	e_to_minus_x proc
		fld x
		fmul minus_one
		fldl2e
		fmul
		fld st
		frndint
		fsub st(1),st
		fxch st(1)
		f2xm1
		fld1
		fadd
		fscale
		fstp st(1)
		fstp brainy_rezult
		ret
	e_to_minus_x endp

	addMember proc
		mov fact, 1
		cmp cx, 0
		jg cont1
			fld plus_one
			fadd stupid_rezult
			fstp stupid_rezult
			ret
		cont1:
		push cx
		finit
		fld x
		dec cx
		cmp cx, 0
		je cont2
		lp_x_to_n:
			fmul x
		loop lp_x_to_n
		cont2:
		fld1
		pop cx
		push cx
		lp_fact_n:
			fimul fact
			inc fact
		loop lp_fact_n
		pop cx
		push cx
		shr cx, 1
		fxch st(1)
		jnc dont_add_minus_one
			fmul minus_one
		dont_add_minus_one:
		fxch st(1)
		fdivp st(1),st
		fadd stupid_rezult
		fstp stupid_rezult
		pop cx
		ret
	addMember endp

	set_accuracy proc
		push ax
		pushf
		fld stupid_rezult
		fabs
		fld previous_stupid_rezult
		fabs
		fsubp
		fabs
		fld required_accuracy
		fabs
		fcompp
		fstsw ax
		sahf
		jc toNormalEnd

			fld stupid_rezult
			fabs
			fld previous_stupid_rezult
			fabs
			fsubp
			fstp factical_accuracy

			mov num_of_members,esi
			popf
			pop ax
			jmp countedMember
		toNormalEnd:
			popf
			pop ax
			ret
	set_accuracy endp

	save_previous_stupid_rezult proc
		fld stupid_rezult
		fstp previous_stupid_rezult
		ret
	save_previous_stupid_rezult endp

	move_to_next_x proc
		fld x
		fadd x_step
		fstp x
		ret
	move_to_next_x endp

	load_stepnum_to_cx proc
		fld x_end
		fld x
		fsubp
		fld x_step
		fdivp
		frndint
		fistp num_of_steps
		mov ecx, num_of_steps
		ret
	load_stepnum_to_cx endp

	read_to_st proc
		mov ah,0Ah              ;������� DOS 0Ah - ���� ������ � �����
        mov [buffer],254        ;������ ������������ ����� � ������ ���� ������
        mov byte[buffer+1],0    ;��������� ������� ����� (����������� �����)
        mov dx,offset buffer    ;DX = a���� ������
        int 21h                 ;��������� � ������� DOS
		mov ah,09h
		mov dx,offset new_line
		int 21h

	cont_1:
		mov cl, buffer[1]       ;length of string to cl
		xor ch, ch
		finit                   ;initialization of soprocessor
		fld ten                 ;10.0 ->st(0)
		fldz                    ;0->st(0), 10 ->st(1)
		lea si,buffer           ;offset buffer -> si
		add si,cx               ;in si - offset to sublast symbol in buffer
		inc si                  ;in si - offset to the last symbol in buffer
		std                     ;d = 1
		xor ax,ax

	m1:                         ;float part
		lodsb                   ;[ds:si] -> al
		cmp al,"."              ;in al dot?
        je  m2                  ;yes
		and al,0fh              ;ASCII->BCD
		mov u_n,ax
		fiadd u_n               ;���������� ��������� ����� � �������� � ����� ������������
		fdiv st(0),st(1)        ;����� �������� � ������� ����� �� 10
		dec cx                  ;decrement for length of string
		inc count               
		jmp m1

	m2:                         ;int part
		dec cx
		mov si, offset buffer
		add si, 2               ;si -> first symbol of string
		fldz                    ;0->st(0), float part->st(1), 10->st(2)
	m3:
		mov al, [si]            ;symbol from string -> al
		and al, 0Fh             ;ASCII->BCD
		fmul st(0), st(2)       ;st(0)=st(0)*st(2)=st(0)*10
		mov u_n, ax             
		fiadd u_n               ;st(0)+u_n->st(0)
		inc si                  ;next symbol
		loop m3                 ;while there are symbols
		fadd                    ;st(0)+st(1)->st(0) or int part + float part -> st(0)
		ret
	read_to_st endp

	show_atomic_rezult proc
		push dx
		push ax

		mov ah,09h
		mov dx, offset atomic_rezult
		int 21h

		fld x
		fsub x_step
    		CALL float_number_to_string
    		CALL show_float_converted

    		mov ah,09h
		mov dx, offset atomic_rezult1
		int 21h

		fld brainy_rezult
    		CALL float_number_to_string
    		CALL show_float_converted

    		mov ah,09h
		mov dx, offset atomic_rezult2
		int 21h

		fld stupid_rezult
    		CALL float_number_to_string
    		CALL show_float_converted

    		mov ah,09h
		mov dx, offset atomic_rezult3
		int 21h

		fild num_of_members
    		CALL float_number_to_string
    		CALL show_float_converted

    		mov ah,09h
		mov dx, offset atomic_rezult4
		int 21h

		pop ax
		pop dx
		ret
	show_atomic_rezult endp

	;
    ;procedures
    ;

    ceil_mode proc
        fstcw cw_buffer
        and cw_buffer,1111001111111111b
        or cw_buffer,1111011111111111b
        fldcw cw_buffer
        ret
    ceil_mode endp

    default_mode proc
        fstcw cw_buffer
        and cw_buffer,1111001111111111b
        fldcw cw_buffer
        ret
    default_mode endp

    revert_str proc
        push eax
        push edx
        xor di,di
        mov si,cx
        dec si
        lp_revert_str:
            mov al,[bx][di]
            mov dl,[bx][si]
            xchg eax,edx
            mov [bx][di],al
            mov [bx][si],dl
            inc di
            dec si
            cmp si,di
            jl exit_lp_revert_str
        loop lp_revert_str
        exit_lp_revert_str:
        pop edx
        pop eax
        ret
    revert_str endp

    int_part_to_str proc
        push si
        push cx
        push dx

        xor si,si
        mov num_str[si],36
        inc si
        mov num_str[si],46
        inc si

        fild int_buf
        fldz
        fcompp
        fstsw ax
        sahf
        jnz convert_int
            mov num_str[si],48
            inc si
            jmp int_converted
        convert_int:
            fild int_buf
            fldz
            fcomp
            fstsw ax
            sahf
                jz int_converted
            fld ten
            fdivp
            fst st(1)
            frndint
            fist int_buf
            fsubp
            fld ten
            fmulp

            fldz
            fcomp
            fstsw ax
            sahf
            jnz not_zero_got
                fsub one 

			
            not_zero_got:

			fld five
            fcomp
            fstsw ax
            sahf
            jnz not_five_got
                fsub one 

			not_five_got:
            fadd ascii_m
            fistp  int_tmp
            mov eax,int_tmp
            mov num_str[si],al
            inc si
        jmp convert_int
        int_converted:
        cmp minus,0
        je cont_without_minus
            mov num_str[si],45
            inc si
        cont_without_minus:
        mov cx,si
        mov bx,offset num_str
        CALL revert_str
        
        pop dx
        pop cx
        pop si
        ret
    int_part_to_str endp

    float_part_to_str proc
        push si
        push bx
        push dx
        push cx

        xor si,si
        mov float_str[si],36
        inc si
        mov ecx,int_num_of_pre_zeros
        
        
        convert_float:
            fild float_buf
            fldz
            fcomp
            fstsw ax
            sahf
                jz float_converted
            fld ten
            fdivp
            fst st(1)
            frndint
            fist float_buf
            fsubp
            fld ten
            fmulp

            fldz
            fcomp
            fstsw ax
            sahf
            jnz not_zero_got_float
                fsub one 
            
            not_zero_got_float:

			fld five
            fcomp
            fstsw ax
            sahf
            jnz not_five_got_float
                fsub one 

			not_five_got_float:
            fadd ascii_m
            frndint
            fistp  int_tmp
            mov eax,int_tmp
            mov float_str[si],al
            inc si
        jmp convert_float
        float_converted:

        mov ecx,int_num_of_pre_zeros
        cmp ecx,0
        jle no_add_invisible_zeros
        add_invisible_zeros:
            mov float_str[si],48
            inc si
        loop add_invisible_zeros
        no_add_invisible_zeros:

        mov cx,si
        mov bx,offset float_str
        CALL revert_str

        pop cx
        pop dx
        pop bx
        pop si
        ret
    float_part_to_str endp

    take_int_part proc
        push ax

        fldz
        fcomp
        fstsw ax
        sahf
        jc not_minus
            mov minus,1
            fabs
        not_minus:
        fst st(1)       ;take int part to int_buf
        frndint
        fist int_buf

        pop ax
        ret
    take_int_part endp

    take_float_part proc
        push ax
        push cx

        fsubp           ;take float part to float_buf
        mov cx,8
        cont_search:
            fld ten
            fmul
            fst st(1)
            frndint
            fcomp
            fstsw ax
            sahf
            jz store_float
        loop cont_search
        store_float:
        frndint
        fist float_buf

        pop cx
        pop ax
        ret
    take_float_part endp

    float_number_to_string proc
		mov int_num_of_pre_zeros,0
		mov minus,0
        CALL ceil_mode
        CALL take_int_part
        CALL take_float_part
        CALL int_part_to_str
        CALL float_part_to_str
        CALL default_mode
        ret
    float_number_to_string endp

    show_float_converted proc
        push ax
        push dx

        mov ah,09h
        mov dx,offset num_str
        int 21h
        mov ah,09h
        mov dx,offset float_str
        int 21h

        pop dx
        pop ax
        ret
    show_float_converted endp

CODE ENDS
END START