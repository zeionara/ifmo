.586
.model flat, stdcall

extern FindWindowA@8:near
extern SetWindowTextA@8:near

includelib D:\Applications\masm32\lib\user32.lib

data segment
  titl db "Calculator",0
  newtitl db "Calhuiator",0
data ends

text segment
start:
  push offset titl
  push 0
  call FindWindowA@8

  push offset newtitl
  push eax
  call SetWindowTextA@8
  ret
text ends
end start
