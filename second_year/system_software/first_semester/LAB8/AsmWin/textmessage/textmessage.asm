.586
.model flat, stdcall

extern MessageBoxA@16:near

includelib D:\Applications\masm32\lib\user32.lib

data segment
  head db "Windows 10 or Linux?",0
  mess db "I use Windows 10",0
data ends

text segment
start:
  push 0
  push offset head
  push offset mess
  push 0
  call MessageBoxA@16
  ret
text ends
end start
