.386
.model flat,stdcall

option casemap:none
include D:\Applications\masm32\include\windows.inc
include D:\Applications\masm32\include\user32.inc
include D:\Applications\masm32\include\kernel32.inc

includelib D:\Applications\masm32\lib\user32.lib
includelib D:\Applications\masm32\lib\kernel32.lib

.data
appName db "Testing lab 7",0
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

.code
jmp start
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


  start:
  invoke MessageBox,NULL,addr atomic_rezult,addr appName,MB_OK
  mov eax, offset begin_x_got
  mov x0s, eax
  mov eax, offset end_x_got
  mov xns, eax
  mov eax, offset x_step_got
  mov steps, eax
  mov eax, offset x_acc_got
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
  invoke MessageBox,NULL,addr table_head,addr appName,MB_OK

  ret
end start
