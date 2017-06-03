.386
.model flat,stdcall
option casemap:none
include D:\Applications\masm32\include\windows.inc
include D:\Applications\masm32\include\user32.inc
include D:\Applications\masm32\include\kernel32.inc

includelib D:\Applications\masm32\lib\kernel32.lib
includelib D:\Applications\masm32\lib\user32.lib

.data
  LibName db "library.dll",0
  FunctionName db "TestFunction",0
  DllNotFound db "Cannot load library",0
  AppName db "Load Library",0
  allPerfect db "Whaaaaaaaat",0
  FunctionNotFound db "TestHello function not found",0

.data?
  hLib dd ?
  TestHelloAddr dd ?
  sega dd ?

.code
  start:
    invoke LoadLibrary,addr LibName

    .if eax==NULL
      invoke MessageBox,NULL,addr DllNotFound,addr AppName,MB_OK
    .else
      mov hLib,eax
      invoke GetProcAddress,hLib,addr FunctionName

      .if eax==NULL
        invoke MessageBox,NULL,addr FunctionNotFound,addr AppName,MB_OK
      .else
        mov TestHelloAddr,eax
        push offset allPerfect
        call [TestHelloAddr]
      .endif

      invoke FreeLibrary,hLib

    .endif
    invoke ExitProcess,NULL
  end start
