.586
.model flat,stdcall

extern FindWindowA@8:near
extern SendMessageA@16:near

includelib D:\Applications\masm32\lib\user32.lib

data segment
  className db "CalcFrame",0
  titl db "Calculator",0
data ends

text segment
start:
  push offset titl
  push 0
  call FindWindowA@8

  push 0
  push 0
  push 16
  push eax
  call SendMessageA@16

  ret
text ends
end start
