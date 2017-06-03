.386
.model flat,stdcall

option casemap:none
include D:\Applications\masm32\include\windows.inc
include D:\Applications\masm32\include\user32.inc
include D:\Applications\masm32\include\kernel32.inc

includelib D:\Applications\masm32\lib\user32.lib
includelib D:\Applications\masm32\lib\kernel32.lib

.data
  allPerfect db "All perfect!",0
  AppName db "Lib",0
  ;first lab data
  arr1 dd -11,-2,-13,42,56,-6,71,8,-9,10,11,-12,13  ;original array
  g1 dd 0FFFFh  ;delemiter
  arr2 dd 13 dup (0) ;additional array
  g2 dd 0FFFFh  ;delemiter
  arr3 dd 13 dup (0)  ;additional array
  numofpoesitives dd ?  ;number of positives in original
  esizeofel = 4

  last dd ?
  greatest dd ?
  meedium dd ?

  gf dd 0FFFh
  arrfinal dd 13 dup(0)
  esizefinal dd ?

  beginning db "Beginning ... ",0
  appName db "DLL",0
  ending db "ending ... ",0
  ;second lab data
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
	msk_o dq 0FEDCBA9876543210h


	msk_l dd 0FFFFF000h
	msk_h dd 0000FFFFFh
  FontName db "Courier New",0
  hFont dd ?
  ;seventh lab data
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
  num_str db 100 DUP (32),0
  float_str db 100 DUP (32),0
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
  atomic_rezult db "     ",0
  atomic_rezult1 db "     ",0
  atomic_rezult2 db "     ",0
  atomic_rezult3 db "     ",0
  atomic_rezult4 db 0ah,0
  cur_iteration dd 0
  debug_msg db "I am here",0
  cm dd 0

  x0s dd 0
  xns dd 0
  steps dd 0
  accs dd 0

  ;input
  begin_x_got db "1.11",0
  end_x_got db "1.19",0
  x_step_got db "0.01",0
  x_acc_got db "0.00001",0

  ;output
  table_head db "               x           by function     by rows      num of membs ",0ah
  output db 10000 DUP(?)
  output_offset dd 0
  dot db ".",0
  space db " ",0
  counter dd 0
  retaddr dd 0
  lb7_debug db "Lab7 debug",0

  esp_saved dd 0
  ebp_saved dd 0
.code

  DllEntry proc hInstDLL:HINSTANCE, reason:DWORD, reserved1:DWORD
    mov  eax,TRUE
    ret
  DllEntry Endp

  TestFunction proc content:LPCTSTR
    invoke MessageBox,NULL,content,addr AppName,MB_OK
    ret
  TestFunction endp

  FirstLab proc aac:LPDWORD
    ;first part - get array, containing negative elements from original at the beginning and sorted positives - at the end
    mov ebx, aac
    mov [ebx], offset arrfinal

    mov ecx,13
    xor esi,esi
    xor edi,edi

    lp1: ;Copying negatives to arr2
      mov edx,arr1[esi]
      cmp edx,0
      jg morethanzero
          mov arr2[edi],edx
          add edi,esizeofel
      morethanzero:
          ADD esi,esizeofel
    loop lp1

    mov ecx,13
    xor esi,esi
    xor edi,edi

    lp2: ;Copying positives to arr3
      mov edx,arr1[esi]
      cmp edx,0
      jle lessethanzero
          mov arr3[edi],edx
          add edi,esizeofel
      lessethanzero:
          add esi,esizeofel
    loop lp2

    xor esi,esi
    mov esi, esizeofel
    continue_shift:
      shr esi,1
      shr edi,1
      cmp esi, 0
    jg continue_shift
    mov ecx,edi
    mov numofpoesitives,ecx
    xor edi,edi

    sort_external_loop:  ; External loop of bubblesort
      mov edx,arr3[esi]
      mov edi,esi
      push ecx
      dec ecx
      cmp ecx,0
      jle end_of_sort
      sort_internal_loop:  ; Internal loop of bubblesort
        add edi,esizeofel
        mov eax,arr3[edi]
        cmp edx,eax
        jl bubble_up
        jmp final_internal_loop
        bubble_up:
          xchg edx,eax
          mov arr3[edi],eax
          mov arr3[esi],edx
        final_internal_loop:
      loop sort_internal_loop
      pop ecx
      add esi,esizeofel
    loop sort_external_loop
    end_of_sort:

    xor esi,esi
    xor edi,edi
    mov ecx,numofpoesitives
    mov edi,48

    replacing: ; Copying elements from arr3 to the end of arr2
      mov edx,arr3[esi]
      mov arr2[edi],edx
      add esi,esizeofel
      sub edi,esizeofel
    loop replacing

    ;THE
    ;SECOND
    ;PART

    mov esi,48
    mov edx, arr1[esi]
    mov last,edx

    mov ecx, numofpoesitives
    cmp ecx, 0
    jle find_greatest
    xor esi,esi
    mov edx,arr3[esi]
    mov greatest, edx
    jmp cmeedium

    ; If there are not positives, then sort original array for fineding greatest value

    find_greatest:
    xor esi,esi
    xor edi,edi
    mov ecx,13

    sort_1_external_loop:
      mov edx,arr1[esi]
      mov edi,esi
      push ecx
      dec ecx
      cmp ecx,0
      jle end_of_sort_1
      sort_1_internal_loop:
        add edi,esizeofel
        mov eax,arr1[edi]
        cmp edx,eax
        jl bubble_up_1
        jmp final_sort_1
        bubble_up_1:
          xchg edx,eax
          mov arr1[edi],eax
          mov arr1[esi],edx
        final_sort_1:
      loop sort_1_internal_loop
      pop ecx
      add esi,esizeofel
    loop sort_1_external_loop
    end_of_sort_1:

    XOR esi,esi
    MOV edx,arr1[esi]
    MOV greatest, edx

    cmeedium:
    MOV edx, last
    ADD edx, greatest
    SHR edx, 1
    MOV meedium, edx

    XOR esi,esi
    XOR edi,edi
    MOV ecx,13
    LEA ebx,arr2

    lp3:
      mov eax,[ebx + esi]
      cmp eax,edx
      jle continue
      push ebx
      lea ebx,arrfinal
      mov [ebx + edi], eax
      add edi, esizeofel
      pop ebx
      continue:
      ADD esi, esizeofel
    loop lp3

    SHR edi,2
    MOV ecx, edi
    MOV esizefinal, ecx

    ret
  FirstLab endp

  SecLab proc
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
   ret
  SecLab endp

  SevLab proc x0str:LPCTSTR, xnstr:LPCTSTR, step:LPCTSTR, acc:LPCTSTR, retta:LPVOID
  invoke MessageBox,NULL,addr lb7_debug,addr appName,MB_OK
  ;ret
  mov esp_saved, esp
  mov ebp_saved, ebp


  ;pop retaddr
  ;pop eax
  ;pop ebx

  mov eax, x0str
  mov x0s, eax
  mov eax, xnstr
  mov xns, eax
  mov eax, step
  mov steps, eax
  mov eax, acc
  mov accs, eax
  mov cm, countedMember

  push x0s
  CALL read_to_st
  fstp x

  push xns
  CALL read_to_st
  fstp x_end

  push steps
  CALL read_to_st
  fstp x_step

  push accs
  CALL read_to_st
  fstp required_accuracy

  ;
  ;counting
  ;

  CALL load_stepnum_to_cx
  mov counter, ecx
  xor esi,esi
  lp_brainy:
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
    push ecx
    mov ecx, 100
    xor esi,esi
    lp1:
      push ecx
      mov ecx, esi
      CALL addMember
      pop ecx
      inc esi
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
    pop ecx
    pop ecx
    dec counter
    mov ecx,counter
    cmp ecx,0
    jge coo
      jmp exitter

    coo:
  loop lp_brainy
  exitter:
  ;invoke MessageBox,NULL,addr table_head,addr appName,MB_OK
  invoke MessageBox,NULL,addr table_head,addr appName,MB_OK

  ;invoke ExitProcess, 0
  mov esp, esp_saved
  mov ebp, ebp_saved
    ret
  SevLab endp

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
    push eax
    pushf
    fld stupid_rezult
    fabs
    fld previous_stupid_rezult
    fabs
    fsubp st(1),st
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
      fsubp st(1),st
      fstp factical_accuracy

      mov num_of_members,esi
      popf
      pop eax
      jmp cm
    toNormalEnd:
      popf
      pop eax
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
    fsubp st(1),st
    fld x_step
    fdivp st(1),st
    frndint
    fistp num_of_steps
    mov ecx, num_of_steps
    ret
  load_stepnum_to_cx endp

  read_to_st proc
    mov ebp, esp
    mov ebx, [ebp + 4]
    xor esi, esi
    xor ecx, ecx
    ;invoke MessageBox,NULL,ebx,addr appName,MB_OK
    lp0:
      mov al, [ebx+esi]
      cmp al, 0
      jle lp0_exit
      add esi, 1
    jmp lp0
    lp0_exit:

    mov ecx, esi
    cont_1:
    xor ch, ch

    finit                   ;initialization of soprocessor

    fld ten                 ;10.0 ->st(0)

    fldz                    ;0->st(0), 10 ->st(1)

    mov esi,ebx           ;offset buffer -> si
    add esi,ecx               ;in si - offset to afterlast symbol in buffer
    sub esi, 1                  ;in si - offset to the last symbol in buffer

    xor ax,ax

    m1:                         ;float part
      mov al, [esi]                   ;[ds:si] -> al
      cmp al,"."              ;in al dot?
      je  m2                  ;yes
      and al,0fh              ;ASCII->BCD
      mov u_n,ax
      fiadd u_n
      fdiv st(0),st(1)
      dec ecx                  ;decrement for length of string
      dec esi
      inc count
      jmp m1

    m2:                         ;int part
      dec ecx
      mov esi, ebx
      ;add si, 2               ;si -> first symbol of string
      fldz                    ;0->st(0), float part->st(1), 10->st(2)
    m3:
      mov al, [esi]            ;symbol from string -> al
      and al, 0Fh             ;ASCII->BCD
      fmul st(0), st(2)       ;st(0)=st(0)*st(2)=st(0)*10
      mov u_n, ax
      fiadd u_n               ;st(0)+u_n->st(0)
      inc esi                  ;next symbol
      loop m3                 ;while there are symbols
    fadd                    ;st(0)+st(1)->st(0) or int part + float part -> st(0)
    ret
  read_to_st endp

  add_str_to_output proc
    push ebx
    push esi
    push edi
    push edx
    push ecx
    push eax

    mov ebx, offset output
    xor esi, esi
    xor edi, edi
    mov edi, output_offset
    mov ebp, esp
    mov edx, [ebp + 28]
    ;invoke MessageBox,NULL,edx,addr appName,MB_OK
    mov ecx, 100
    lp_adding_to_output:
      mov al, [edx + esi]
      cmp al, 0
      jle end_of_adding_to_output
      mov [ebx + edi], al
      inc edi
      inc esi
      inc output_offset
    loop lp_adding_to_output
    end_of_adding_to_output:
    xor al,al
    mov [ebx + edi], al

    pop eax
    pop ecx
    pop edx
    pop edi
    pop esi
    pop ebx
    ret
  add_str_to_output endp

  show_atomic_rezult proc
    push dx
    push ax

    ;invoke MessageBox,NULL,addr atomic_rezult,addr appName,MB_OK
    ;push eax
    ;mov eax, offset atomic_rezult
    ;push eax
    ;call add_str_to_output
    push offset atomic_rezult
    call add_str_to_output
    pop eax
    ;pop eax
    fld x
    fsub x_step

    CALL float_number_to_string

    CALL show_float_converted


    ;mov ah,09h
    ;mov dx, offset atomic_rezult1;-----------------------------------------------------------------------------------------------------------------------------------------
    ;int 21h

    ;push eax
    ;mov eax, offset atomic_rezult1
    ;push eax
    ;call add_str_to_output
    ;invoke MessageBox,NULL,addr output,addr appName,MB_OK
    ;pop eax

    push offset atomic_rezult1
    call add_str_to_output
    pop eax
    ;invoke MessageBox,NULL,addr atomic_rezult1,addr appName,MB_OK
    fld brainy_rezult
        CALL float_number_to_string
        CALL show_float_converted
        ;invoke MessageBox,NULL,addr output,addr appName,MB_OK
    ;mov ah,09h
    ;mov dx, offset atomic_rezult2
    ;int 21h
    ;invoke MessageBox,NULL,addr atomic_rezult2,addr appName,MB_OK
    push offset atomic_rezult2
    call add_str_to_output
    pop eax

    fld stupid_rezult
    call float_number_to_string
    call show_float_converted

    ;mov ah,09h
    ;mov dx, offset atomic_rezult3
    ;int 21h
    ;invoke MessageBox,NULL,addr atomic_rezult3,addr appName,MB_OK
    push offset atomic_rezult3
    call add_str_to_output
    pop eax

    fild num_of_members
        CALL float_number_to_string
        CALL show_float_converted

    ;mov ah,09h
    ;mov dx, offset atomic_rezult4
    ;int 21h
    push offset atomic_rezult4
    call add_str_to_output
    pop eax

    ;nvoke MessageBox,NULL,addr table_head,addr appName,MB_OK
    pop ax
    pop dx
    ret
  show_atomic_rezult endp
  show_float_converted proc
      push eax
      push edx
      push esi

      push offset num_str
      call add_str_to_output
      pop eax

      xor esi, esi
      cmp float_str[esi], 0
      jle finish
      push offset dot
      call add_str_to_output
      pop eax

      push offset float_str
      call add_str_to_output
      pop eax

      finish:
      pop esi
      pop edx
      pop eax
      ret
  show_float_converted endp

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
        xor edi,edi
        mov esi,ecx
        dec esi
        lp_revert_str:
            ;invoke MessageBox,NULL,ebx,addr appName,MB_OK
            mov al,[ebx][edi]
            mov dl,[ebx][esi]
            xchg eax,edx

            mov [ebx][edi],al
            mov [ebx][esi],dl
            inc edi
            dec esi
            cmp esi,edi
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

        xor esi,esi

        mov num_str[esi],36

        inc esi
        mov num_str[esi],0
        inc esi

        fild int_buf
        fldz
        fcompp
        fstsw ax
        sahf
        jnz convert_int
            mov num_str[esi],48
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
            fdivp st(1),st
            fst st(1)
            frndint
            fist int_buf
            fsubp st(1),st
            fld ten
            fmulp st(1),st

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
            mov num_str[esi],al
            inc esi
        jmp convert_int
        int_converted:
        cmp minus,0
        je cont_without_minus
            mov num_str[esi],45
            inc esi
        cont_without_minus:
        mov ecx,esi
        mov ebx,offset num_str

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
        mov float_str[si],0
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
            fdivp st(1),st
            fst st(1)
            frndint
            fist float_buf
            fsubp st(1),st
            fld ten
            fmulp st(1),st

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
        mov ebx,offset float_str
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
        push eax
        push ecx

        fsubp st(1),st          ;take float part to float_buf
        mov ecx,8
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

        pop ecx
        pop eax
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
End DllEntry
