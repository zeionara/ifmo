ml /c /coff uselibrary.asm
link /subsystem:windows uselibrary.obj
uselibrary
g++ uselibrary.cpp -o uselibrary
uselibrary
