g++ -c -DBUILDING_LIBRARY_DLL library_c.cpp
g++ -shared -o library_c.dll library_c.o -Wl,--out-implib,libexample_dll.a
