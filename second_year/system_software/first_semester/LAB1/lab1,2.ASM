STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    ; Original array
    arr1 dw -11,-2,-13,42,56,-6,71,8,-9,10,11,-12,13
    
    ; delemiter in memory
    g1 dw 0FFh
    
    ; Additional array
    arr2 dw 13 dup (0)
    
    ; delemiter in memory
    g2 dw 0FFh
    
    ; Additional array
    arr3 dw 13 dup (0)
    
    ; Number of positive numbers in original array
    numofpositives dw ?

    sizeofel = 2

    last dw ?
    greatest dw ?
    medium dw ?

    arrfinal dw 13 dup(0)
    sizefinal dw ?
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    ; Loading DS
    MOV AX, DATA
    MOV DS, AX
    
    ;THE
    ;FIRST
    ;PART

    ; Prepearing to copying negatives to arr2
    MOV cx,13
    XOR si,si
    XOR di,di

    ;Copying negatives to arr2
    lp1:
        MOV dx,arr1[si]
        CMP dx,0
        JG morethanzero
            MOV arr2[di],dx
            ADD di,sizeofel
        morethanzero:
            ADD si,sizeofel
    loop lp1

    ; Prepearing to copying positives to arr3
    XOR si,si
    XOR di,di
    MOV cx,13

    ;Copying positives to arr2
    lp2:
        MOV dx,arr1[si]
        CMP dx,0
        JLE lessethanzero
            MOV arr3[di],dx
            ADD di,sizeofel
        lessethanzero:
            ADD si,2
    loop lp2

    ; Prepearing to bubblesort arr3
    XOR si,si
    ; Saving number of positives = di/sizeofel
    SHR di,1
    MOV cx,di
    MOV numofpositives,cx
    XOR di,di


    ; Outer cycle of bubblesort
    sort1:
        MOV dx,arr3[si]
        MOV di,si
        PUSH cx
        DEC cx
        CMP cx,0
        JLE endofsort
        ; Inner cycle of bubblesort
        sort2:
            ADD di,sizeofel            
            MOV ax,arr3[di]
            CMP dx,ax
            JL bubbleup
            JMP finalsort2
            bubbleup:
                XCHG dx,ax
                MOV arr3[di],ax
                MOV arr3[si],dx
            finalsort2:
        loop sort2
        POP cx
        ADD si,sizeofel
    loop sort1
    endofsort:


    ; Prepearing to copying values from arr3 to arr2
    XOR si,si
    XOR di,di
    MOV cx,numofpositives
    MOV di,24

    ; Copying elements from arr3 to the end of arr2
    replacing:	
        MOV dx,arr3[si]
        MOV arr2[di],dx
        ADD si,sizeofel
        SUB di,sizeofel
    loop replacing

    ;THE
    ;SECOND
    ;PART

    ;Saving last element in original array
    MOV si,24
    MOV dx, arr1[si]
    MOV last,dx

    ; If there is positives,
    MOV cx, numofpositives
    CMP cx, 0
    ; then select greatest,
    JLE findgreatest
    XOR si,si
    MOV greatest, arr3[si]

    ; If no, then sort original array for finding greatest value
    findgreatest:
    XOR si,si
    XOR di,di
    MOV cx,13
    
    ; Outer cycle of bubblesort
    sort1f:
        MOV dx,arr1[si]
        MOV di,si
        PUSH cx
        DEC cx
        CMP cx,0
        JLE endofsortf
        ; Inner cycle of bubblesort
        sort2f:
            ADD di,sizeofel            
            MOV ax,arr1[di]
            CMP dx,ax
            JL bubbleupf
            JMP finalsort2f
            bubbleupf:
                XCHG dx,ax
                MOV arr1[di],ax
                MOV arr1[si],dx
            finalsort2f:
        loop sort2f
        POP cx
        ADD si,sizeofel
    loop sort1f
    endofsortf:
    ; and take greatest
    XOR si,si
    MOV greatest, arr1[si]

    ; Count medium of last and greatest
    MOV dx, last
    ADD dx, greatest
    SHR dx, 1
    MOV medium

    ; Then compare all elements from arr2 with medium and create final array
    XOR si,si
    XOR di,di
    MOV cx,13
    LEA bx,arr2

    lp3:
        MOV ax,[bx + si]
        CMP ax,dx
        JLE continue
            PUSH bx
            LEA bx,arrfinal
            MOV [bx + di], ax
            ADD di, sizeofel
            POP bx
        continue:
            ADD si, sizeofel
    loop lp3

    SHR di,1
    MOV cx, di
    MOV sizefinal, cx

    ; Now in arrfinal final version of array
    ; In sizefinal and cx - length of final array
    
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START