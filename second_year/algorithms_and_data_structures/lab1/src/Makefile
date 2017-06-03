#rmdir /s /q data
#mkdir data
.PHONY: all run clean makedirs rewindbuild quick_rerun compile_filegen compile_filehash

all: rewindbuild compile_filegen compile_filehash

rerun: clean makedirs run

quick_rerun: rewindbuild run

compile_filegen: filegen.cpp
	g++ filegen.cpp -o build/filegen

compile_filehash: filehash.cpp
	g++ filehash.cpp -o build/filehash

run: main.cpp
	g++ main.cpp -o build/main
	build/main

makedirs:
	mkdir build


clean:
	rmdir /s /q build


rewindbuild:
	rmdir /s /q build
	mkdir build
