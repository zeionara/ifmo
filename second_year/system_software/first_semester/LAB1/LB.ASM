STACK SEGMENT PARA STACK 'stack'
    DB 100H DUP(?)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
    ; Original array
    arr1 dd -11,-2,-13,42,56,-6,71,8,-9,10,11,-12,13
    
    ; delemiter in memory
    g1 dd 0FFFFh
    
    ; Adeditional array
    arr2 dd 13 dup (0)
    
    ; delemiter in memory
    g2 dd 0FFFFh
    
    ; Adeditional array
    arr3 dd 13 dup (0)
    
    ; Number of poesitive numbers in original array
    numofpoesitives dd ?

    esizeofel = 4

    last dd ?
    greatest dd ?
    meedium dd ?

    gf dd 0FFFh
    arrfinal dd 13 dup(0)
    esizefinal dd ?
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    ; Loaeding DS
    MOV AX, DATA
    MOV DS, AX

    .386
    ;THE
    ;FIRST
    ;PART

    ; Prepearing to copying negatives to arr2
    MOV cx,13
    XOR esi,esi
    XOR edi,edi

    ;Copying negatives to arr2
    lp1:
        MOV edx,arr1[esi]
        CMP edx,0
        JG morethanzero
            MOV arr2[edi],edx
            ADD edi,esizeofel
        morethanzero:
            ADD esi,esizeofel
    loop lp1

    ; Prepearing to copying poesitives to arr3
    XOR esi,esi
    XOR edi,edi
    MOV cx,13

    ;Copying poesitives to arr2
    lp2:
        MOV edx,arr1[esi]
        CMP edx,0
        JLE lessethanzero
            MOV arr3[edi],edx
            ADD edi,esizeofel
        lessethanzero:
            ADD esi,2
    loop lp2

    ; Prepearing to bubblesort arr3
    XOR esi,esi
    ; Saving number of poesitives = edi/esizeofel
    SHR edi,1
    MOV ecx,edi
    MOV numofpoesitives,ecx
    XOR edi,edi


    ; Outer cycle of bubblesort
    sort1:
        MOV edx,arr3[esi]
        MOV edi,esi
	PUSH ecx
	DEC ecx
	CMP ecx,0
        JLE endofsort
        ; Inner cycle of bubblesort
        sort2:
            ADD edi,esizeofel            
            MOV eax,arr3[edi]
            CMP edx,eax
            JL bubbleup
            JMP finalsort2
            bubbleup:
                XCHG edx,eax
                MOV arr3[edi],eax
                MOV arr3[esi],edx
            finalsort2:
        loop sort2
	POP ecx
        ADD esi,esizeofel
    loop sort1
    endofsort:


    ; Prepearing to copying values from arr3 to arr2
    XOR esi,esi
    XOR edi,edi
    MOV ecx,numofpoesitives
    MOV edi,48

    ; Copying elements from arr3 to the end of arr2
    replacing:	
        MOV edx,arr3[esi]
        MOV arr2[edi],edx
        ADD esi,esizeofel
        SUB edi,esizeofel
    loop replacing

    ;THE
    ;SECOND
    ;PART

    ;Saving last element in original array
    MOV esi,24
    MOV edx, arr1[esi]
    MOV last,edx

    ; If there is poesitives,
    MOV ecx, numofpoesitives
    CMP ecx, 0
    ; then select greatest,
    JLE findgreatest
    XOR esi,esi
    MOV edx,arr3[esi]
    MOV greatest, edx
    JMP cmeedium

    ; If no, then sort original array for fineding greatest value
    findgreatest:
    XOR esi,esi
    XOR edi,edi
    MOV ecx,13
    
    ; Outer cycle of bubblesort
    sort1f:
        MOV edx,arr1[esi]
        MOV edi,esi
	PUSH ecx
	DEC ecx
	CMP ecx,0
        JLE endofsortf
        ; Inner cycle of bubblesort
        sort2f:
            ADD edi,esizeofel            
            MOV eax,arr1[edi]
            CMP edx,eax
            JL bubbleupf
            JMP finalsort2f
            bubbleupf:
                XCHG edx,eax
                MOV arr1[edi],eax
                MOV arr1[esi],edx
            finalsort2f:
        loop sort2f
	POP ecx
        ADD esi,esizeofel
    loop sort1f
    endofsortf:
    ; and take greatest
    XOR esi,esi
    MOV edx,arr1[esi]
    MOV greatest, edx

    cmeedium:
    ; Count meedium of last and greatest
    MOV edx, last
    ADD edx, greatest
    SHR edx, 1
    MOV meedium, edx

    ; Then compare all elements from arr2 with meedium and create final array
    XOR esi,esi
    XOR edi,edi
    MOV ecx,13
    LEA ebx,arr2

    lp3:
	MOV eax,[ebx + esi]
        CMP eax,edx
        JLE continue
	    PUSH ebx
	    LEA ebx,arrfinal
	    MOV [ebx + edi], eax
            ADD edi, esizeofel
	    POP ebx
        continue:
            ADD esi, esizeofel
    loop lp3

    SHR edi,1
    MOV ecx, edi
    MOV esizefinal, ecx

    ; Now in arrfinal final veresion of array
    ; In esizefinal and ecx - length of final array
    
    ; Returning control to OS
    MOV AX, 4C00H
    INT 21H
CODE ENDS
END START
