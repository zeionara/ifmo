STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    arr1 dw -11,-2,-13,42,56,-6,71,8,-9,10,11,-12,13
    g1 dw 0FFh
    arr2 dw 13 dup (0)
    g2 dw 0FFh
    arr3 dw 13 dup (0)
    numofpositives dw ?
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
    MOV dx,arr1[si]
    CMP dx,0
    JG morethanzero
    MOV arr2[di],dx
    ADD di,2
    morethanzero:
    ADD si,2
    loop lp1	;end cycle
    XOR si,si
    XOR di,di
    MOV cx,13
    lp2:    ;Cycle which copy positive to arr3
    MOV dx,arr1[si]
    CMP dx,0
    JLE lessethanzero
    MOV arr3[di],dx
    ADD di,2
    lessethanzero:
    ADD si,2
    loop lp2	;end cycle
    XOR si,si	;prepare to bubblesort
    SHR di,1
    MOV cx,di
    MOV numofpositives,cx
    XOR di,di

    sort1:	; outer cycle of bubble sort
    MOV dx,arr3[si]
    MOV di,si
    PUSH cx
    DEC cx
    cmp cx,0
    jle endofsort
    sort2:	; inner cycle of bubble sort
    MOV ax,arr3[di]
    CMP dx,ax
    JL bubbleup
    JMP finalsort2
    bubbleup:

    MOV arr3[di],dx
    MOV arr3[si],ax
    finalsort2:
    ADD di,2
    loop sort2	 ; end of inner cycle
    POP cx
    ADD si,2
    loop sort1	 ; end of outer cycle end of sorting arr3
    endofsort:
    XOR si,si
    XOR di,di
    MOV cx,numofpositives
    MOV di,24
    replacing:	; cycle for moving elements from arr3 to the end of arr2
    MOV dx,arr3[si]
    MOV arr2[di],dx
    ADD si,2
    SUB di,2
    loop replacing ; end of cycle
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
