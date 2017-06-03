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
    jc $+02Fh
        clc
            add si, 5
            dec di
            cmp di, 0
        jg $-7
    
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

        jmp $+02Fh

    
        clc
        add si, 2
            add si, 5
            dec di
            cmp di, 0
        jg $-7

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
    jc $+028h
        clc
            add si, 5
            dec di
            cmp di, 0
        jg $-7
        
        mov rgl, byte ptr mas[si] ;read greatest 8 bit
        shl rg, 8

        inc si
        mov rgl, byte ptr mas[si] ;read middle 8 bit
        shl rg, 8
        
        inc si
        mov rgl, byte ptr mas[si] ;read least 4 bit
        shr rg, 4
        
        jmp $+027h

    
        clc
        add si, 2
            add si, 5
            dec di
            cmp di, 0
        jg $-7
        
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
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    ; Loading DS
    MOV AX, DATA
    MOV DS, AX
	.386
	mov edx, -15
    mov eax,  5
    mulEls eax, edx
    mulEls eax, edx
    ;mov eax, 12345678h
    ;addEl eax, al, mas, 7
    ;mov eax, 12345678h
    ;addEl eax, al, mas, 8
    ;readEl eax, al, mas, 8
	

    ; Returning control to OS
	MOV AX, 4C00H
	INT 21H	
CODE ENDS
END START
