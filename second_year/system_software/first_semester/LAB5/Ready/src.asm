STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

addEl macro rg, rgl, mas, index
    push si
    push di
    push rg

    xor si, si
    mov di, index
    
    rcr di, 1
    jc $+032h
        clc
            add si, 5
            dec di
            cmp di, 0
        jge $-7
        
        sub si, 5
        add si, 2
        shl rg, 4
        add rgl, byte ptr mas[si]
        mov byte ptr mas[si], rgl ;write least 4 bit

        dec si
        shr rg, 8
        mov byte ptr mas[si], rgl ;write middle 8 bit

        dec si
        shr rg, 8
        mov byte ptr mas[si], rgl ;write greatest 8 bit

        jmp $+032h

    
        clc
        add si, 2
            add si, 5
            dec di
            cmp di, 0
        jge $-7
        
        sub si, 5
        add si, 2
        mov byte ptr mas[si], rgl ;write least 8 bit

        dec si
        shr rg, 8
        mov byte ptr mas[si], rgl ;write middle 8 bit

        dec si
        shr rg, 8
        and rgl, 0Fh
        add rgl, byte ptr mas[si]
        mov byte ptr mas[si], rgl ;write greatest 4 bit

    pop rg
    pop di
    pop si
endm

readEl macro rg, rgl, mas, index
    push si
    push di

    xor si, si
    mov di, index
    
    rcr di, 1
    jc $+02Bh
        clc
            add si, 5
            dec di
            cmp di, 0
        jge $-7
        
        sub si,5
        mov rgl, byte ptr mas[si] ;read greatest 8 bit
        shl rg, 8

        inc si
        mov rgl, byte ptr mas[si] ;read middle 8 bit
        shl rg, 8
        
        inc si
        mov rgl, byte ptr mas[si] ;read least 4 bit
        shr rg, 4
        
        jmp $+02Bh

    
        clc
        add si, 2
            add si, 5
            dec di
            cmp di, 0
        jge $-7
        
        sub si,5
        mov rgl, byte ptr mas[si] ;read greatest 4 bit
        and rgl, 0Fh
        shl rg, 8

        inc si
        mov rgl, byte ptr mas[si] ;read middle 8 bit
        shl rg, 8

        inc si
        mov rgl, byte ptr mas[si] ;read least 8 bit


    pop di
    pop si
endm

mulEls macro rgs, rgd
    push esi
    push edi
    push bp
    mov bp, sp

    ; check sign of rgs
    shl rgs, 12
    rcl rgs, 1
    jnc $+02Fh
        rcr rgs, 1
        shr rgs, 12
        
        not rgs
        inc rgs

        shl rgd, 12
        rcl rgd, 1
        jnc $+010h
            rcr rgd, 1
            shr rgd, 12
        
            not rgd
            inc rgd
            jmp $+032h
        
            rcr rgd, 1
            shr rgd, 12
            inc bp
        jmp $+028h

        rcr rgs, 1
        shr rgs, 12

        shl rgd, 12
        rcl rgd, 1
        jnc $+011h
            rcr rgd, 1
            shr rgd, 12
        
            not rgd
            inc rgd
            inc bp
            jmp $+09h
        
            rcr rgd, 1
            shr rgd, 12
    ;cont:

    mov edi, 20
    shl rgs, 12
    ;lp1:
        dec di
        cmp di, 0
        jl $+016h

        rcl rgs, 1
        jnc $-09h
            push cx
            mov cx, di
            shl rgd, cl
            add esi, rgd
            shr rgd, cl
            pop cx
            jmp $-018h

    ;toexit:
    mov rgd, esi
    cmp bp, sp
    je $+09h
        not rgd
        inc rgd

    ;finish:
    pop bp
    pop edi
    pop esi
endm


DATA SEGMENT PARA PUBLIC 'data'
    del db 0FFh
    mas db 100h DUP (0)
    num dw 5
    
    ;outputting
    startheader1 db "--rezult--",0Ah,'$';
    startheader db "--source--",0Ah,'$';
    leftbound db "|  ";
    symb1 db 0;
    symb2 db 0;
    symb3 db 0;
    symb4 db 0;
    symb5 db 0;
    rightbound db " |",0Ah,'$';
    stopheader db "----------",0Ah,'$';

DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    ; Loading DS
    MOV AX, DATA
    MOV DS, AX
	.386
	;mov edx, -15
    ;mov eax,  5
    ;mulEls eax, edx
    ;mulEls eax, edx
    mov eax, -7
    addEl eax, al, mas, 0
    
    mov eax, -2
    addEl eax, al, mas, 1

    mov eax, 3
    addEl eax, al, mas, 2

    mov eax, 09h
    addEl eax, al, mas, 3

    mov eax, 0Fh
    addEl eax, al, mas, 4

    ;showing source

    mov ah, 09
    mov dx, offset startheader
    int 21h

    xor cx,cx
    lp3:
        readEl eax, al, mas, cx
        
        CALL show
        
        inc cx

        cmp cx, num
        jge exitlp3
        
        jmp lp3
    exitlp3:

    mov ah, 09
    mov dx, offset stopheader
    int 21h

    ;showing rezult

    mov ah, 09
    mov dx, offset startheader1
    int 21h

    xor di,di
    xor eax, eax
    xor cx,cx
    lp1:
        xor edx, edx
        readEl edx, dl, mas, cx
        mov eax,edx
        inc cx
        cmp cx, num
        jge exitlp1
        xor edx, edx
        readEl edx, dl, mas, cx
        xor esi, esi
        mulEls edx, eax
        xor esi,esi
        CALL show
        
        jmp lp1
    exitlp1:
    xor edx, edx
    readEl edx, dl, mas, 0
    mulEls edx, eax

    CALL show

    mov dx, offset stopheader
    int 21h
	

    ; Returning control to OS
	MOV AX, 4C00H
	INT 21H	

    translate proc
        push dx
        xor dx,dx
        xor ah,ah
        rcr al,1
        rcr dl,1
        
        rcr al,1
        rcr dl,1
        
        rcr al,1
        rcr dl,1
        
        rcr al,1
        rcr dl,1
        clc
        shr dl,4

        add al, 48
        cmp al, 57
        jle cont1
            add al, 7
        cont1:
        
        add dl, 48
        cmp dl, 57
        jle cont2
            add dl, 7
        cont2:

        rcl dl,1
        rcl ax,1
        
        rcl dl,1
        rcl ax,1

        rcl dl,1
        rcl ax,1

        rcl dl,1
        rcl ax,1

        rcl dl,1
        rcl ax,1

        rcl dl,1
        rcl ax,1

        rcl dl,1
        rcl ax,1

        rcl dl,1
        rcl ax,1
        clc
        pop dx
        RET
    translate endp

    translatesimple proc
        xor ah,ah
        and al,0Fh

        add al, 48
        cmp al, 57
        jle cont3
            add al, 7
        cont3:
        
        RET
    translatesimple endp

    show proc
        mov esi, eax
        mov eax, esi
    
        CALL translate
        mov symb5,al
        mov symb4,ah
        shr esi,8
        mov eax, esi

        CALL translate
        mov symb3,al
        mov symb2,ah
        shr esi,8
        mov eax, esi

        CALL translatesimple
        mov symb1,al

        mov ah, 09
        mov dx, offset leftbound
        int 21h
        RET
    show endp
CODE ENDS
END START
