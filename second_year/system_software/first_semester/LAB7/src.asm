STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS
mul10 macro reg

endm


DATA SEGMENT PARA PUBLIC 'data'
    typeX0MSG db "Please, type x0 here :$"
    err1MSG db 0ah,"Invalid argument$"
    buffer db 256 DUP(?),'$'
    ten dd 10.0
    u_n dw 0
    count dw 0
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS: CODE, DS: DATA, SS: STACK
    .386
    START: MOV AX, DATA
    MOV DS, AX
    ;
    mov ah, 10
    mov dx, offset buffer
    int 21h                 ;in buffer - string representation of number

cont_1:
    mov cl, string[1]       ;length of string to cl
    xor ch, ch
    finit                   ;initialization of soprocessor
    fld ten                 ;10.0 ->st(0)
    fldz                    ;0->st(0), 10 ->st(1)
    lea si,string           ;offset buffer -> si
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
    fiadd u_n               ;складываем очередную цифру и значение в стеке сопроцессора
    fdiv st(0),st(1)        ;делим значение в вершине стека на 10
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
    
    

    
    ;
    MOV AX, 4C00H
    INT 21H

    input_str proc
        push cx                 ;Сохранение СX
        mov cx,ax               ;Сохранение AX в CX
        mov ah,0Ah              ;Функция DOS 0Ah - ввод строки в буфер
        mov [buffer],254        ;Запись максимальной длины в первый байт буфера
        mov byte[buffer+1],0    ;Обнуление второго байта (фактической длины)
        mov dx,offset buffer    ;DX = aдрес буфера
        int 21h                 ;Обращение к функции DOS
        mov al,[buffer+1]       ;AL = длина введённой строки
        add dx,2                ;DX = адрес строки
        mov ah,ch               ;Восстановление AH
        pop cx                  ;Восстановление CX
        ret
    input_str endp

    find_dot proc
        push cx
        push dx
        push si
        push di
        xor ax,ax
        xor cx,cx
        xor si,si
        xor di,di
        add di,1
        mov cl,buffer[1]
        add si,2
        lp3:
            mov dl,buffer[si]
            cmp dl,2Eh
            inc si
            je toretdot
        loop lp3
        mov ax,-1
        ret
        toretdot:
        mov ax,si
        pop di
        pop si
        pop dx
        pop cx
        ret
    find_dot endp

    convert_int_to_binary proc
        inc ax      ;in ax - position of dot
        xor cx,cx
        xor si,si
        xor di,di
        add di,1
        mov cl,buffer[1]
        add si,1
        add si,cx
        lp1:
            xor dx,dx
            mov dl,buffer[si]
            cmp dl,2Dh
            je addminus
        sub dl,30h
        cmp dl,0
            jl error1
        cmp dl,9
            jg error1
        dec si
        
        push si         ;dx*=di
        push cx
        mov si,dx
        mov cx,di
        lp2:
            add dx,si
        loop lp2
        sub dx,si
        pop cx
        pop si

        push si         ;di*=10
        mov si,di
        rept 9
            add di, si
        endm
        pop si
        add ax,dx
    loop lp1

    jmp toexit
    addminus:
        cmp cx,1
        jg error1
        not ax
        add ax,1
    jmp toexit
    error1:
        mov ah,09h
        mov dx,offset err1MSG
        int 21h

    toexit:
    convert_int_to_binary endp

    convert_buffer_to_double proc

    convert_buffer_to_double endproc

CODE ENDS
END START