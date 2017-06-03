.586
.model flat, stdcall

extern FindWindowA@8:near
extern ShowWindow@8:near
extern Sleep@4:near

includelib D:\Applications\masm32\lib\user32.lib
includelib D:\Applications\masm32\lib\kernel32.lib

data segment
  titl db "Calculator",0
  hwnd dd ?
data ends

text segment
start:
  push offset titl
  push 0
  call FindWindowA@8

  mov hwnd,eax

  push 0
  push eax
  call ShowWindow@8

  push 5000
  call Sleep@4

  push 5
  push hwnd
  call ShowWindow@8
  ret
text ends
end start
