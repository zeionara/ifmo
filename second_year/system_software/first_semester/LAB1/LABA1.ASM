STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    string db 'begin of data'
    arr1 db 11,-2,-3,4,5,-6,7,8,-9,10,11,-12,13,14
    arr2 db 13 dup (0)
    arr3 db 13 dup (0)
    sim2 db 'f'
    numofpositives db ?
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    MOV AX, DATA
    MOV DS, AX
    MOV CX,13
    XOR si,si
    XOR di,di
    lp1:    ;Cycle which copy negative and zeros to arr2
    MOV dl,arr1[si]
    CMP dl,0
    JG morethanzero
    MOV arr2[di],dl
    INC di
    morethanzero:
    INC si
    loop lp1	;end cycle
    XOR si,si
    XOR di,di
    MOV cx,13
    lp2:    ;Cycle which copy positive to arr3
    MOV dl,arr1[si]
    CMP dl,0
    JLE lessethanzero
    MOV arr3[di],dl
    INC di
    lessethanzero:
    INC si
    loop lp2	;end cycle
    XOR si,si	;prepare to bubblesort
    MOV cx,di
    MOV numofpositives,di
    XOR di,di
    sort1:	; outer cycle of bubble sort
    MOV dl,arr3[si]
    MOV di,si
    PUSH cx
    DEC cx
    sort2:	; inner cycle of bubble sort
    INC di
    MOV al,arr3[di]
    CMP dl,al
    JG bubbleup
    JMP finalsort2
    bubbleup:
    XCHG dl,al
    MOV arr3[di],al
    MOV arr3[si],dl
    finalsort2:
    loop sort2	 ; end of inner cycle
    POP cx
    INC si
    loop sort1	 ; end of outer cycle
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
