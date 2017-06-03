#g++ bases.cpp -o build/bases
#build/bases data/loop.dat
#g++ files.cpp -o build/files
#build/files data/loop.dat
#g++ heaps.cpp -o build/heaps
#build/heaps data/loop.dat


.PHONY: all

all: run

run: mkdirs files.cpp
	g++ files.cpp -o build/files
	build/files data/loop.dat

rerun: clean run

quick_rerun: clean_build quick_run

quick_run: create_build sort.cpp
	g++ main.cpp -o build/main
	build/main data/loop.dat
	g++ sort.cpp -o build/sort
	build/sort data/loop.dat



mkdirs: create_build
	mkdir data

clean: clean_build
	rmdir /q /s data

clean_build:
	rmdir /q /s build

create_build:
	mkdir build
