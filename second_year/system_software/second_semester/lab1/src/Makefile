.PHONY: all run run_tester rerun rerun_tester clean makebuilddir makedatadir

all: makebuilddir makedatadir cpc cpw cpf run run_tester

cpc: cpc.cpp
	g++ cpc.cpp -o build/cpc

cpw: cpw.cpp
	g++ cpw.cpp -o build/cpw

cpf: cpf.cpp
	g++ cpf.cpp -o build/cpf

rerun: clean makebuilddir makedatadir main.cpp
	g++ main.cpp -o build/main
	build/main

run: main.cpp
	g++ main.cpp -o build/main
	build/main

rerun_tester: clean makebuilddir makedatadir tester.cpp
	g++ tester.cpp -o build/tester
	build/tester

run_tester: tester.cpp
	g++ tester.cpp -o build/tester
	build/tester

makebuilddir:
	mkdir build

makedatadir:
	mkdir data

clean:
	rmdir /s /q build
	rmdir /s /q data
