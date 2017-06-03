.586
.model flat, stdcall

extern MessageBoxA@16:near

includelib D:\Applications\masm32\lib\user32.lib

data segment
  head db"Browsers",0
  mess db "Opera",13,
      "Google Chrome",13,
      "Microsoft Edge",13,
      "Mozilla Firefox",13,13,
      "Kill program?",0
data ends

text segment
start:
  push 68
  push offset head
  push offset mess
  push 0
  call MessageBoxA@16

  cmp eax,7
  jz start
  ret
text ends
end start
