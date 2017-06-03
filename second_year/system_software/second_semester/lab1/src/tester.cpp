#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <time.h>
#define BUF_SIZE 256
using namespace std;

int copyByCLib(const char* src, const char* dest){
  FILE *in_file, *out_file;
  char rec[BUF_SIZE];
  size_t bytes_in, bytes_out;

  in_file = fopen(src,"rb");
  if (in_file == NULL){
    return 1;
  }

  out_file = fopen(dest,"wb");
  if (out_file == NULL){
    return 1;
  }

  while((bytes_in = fread(rec, 1, BUF_SIZE, in_file))>0){
    bytes_out = fwrite(rec, 1, bytes_in, out_file);
    if (bytes_out != bytes_in){
      return 2;
    }
  }

  fclose(in_file);
  fclose(out_file);

  return 0;
}

int copyByWin(const char* src, const char* dest){
  HANDLE hIn, hOut;
  DWORD nIn, nOut;
  CHAR Buffer[BUF_SIZE];
  hIn = CreateFile(src, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hIn == INVALID_HANDLE_VALUE){
    return 1;
  }
  hOut = CreateFile(dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hOut == INVALID_HANDLE_VALUE){
    return 1;
  }
  while(ReadFile(hIn,Buffer,BUF_SIZE,&nIn,NULL)&&nIn>0){
    WriteFile(hOut, Buffer, nIn, &nOut, NULL);

    if (nIn != nOut){

      return 2;
    }
  }
  CloseHandle(hIn);
  CloseHandle(hOut);
  return 0;
}

int copyByCopyFile(const char* src, const char* dest){
  if (!CopyFile(src, dest, FALSE)){
    return 1;
  }
  return 0;
}

int createFile(int size){
  ofstream fout("data/file.dat");
  for (int i = 0; i < size; i++){
    fout.write("DATA",1024);
  }
  fout.close();
}

float getTimeExcecuting(int (*func)(const char*, const char*),const char* src, const char* dest){
  float fTimeStart = clock()/(float)CLOCKS_PER_SEC;

  func(src, dest);

  float fTimeStop = clock()/(float)CLOCKS_PER_SEC;
  return fTimeStop - fTimeStart;
}

int initializeCell(){
  cout << "| ";
  cout.setf(ios::left);
  cout.width(10);
  return 0;
}

int showCell(const char* content){
  initializeCell();
  cout << content;
}

int showCell(const char* content, const char* finalizer){
  initializeCell();
  cout << content << finalizer << endl;
}

int showCell(int content){
  initializeCell();
  cout << content;
}

int showCell(float content){
  initializeCell();
  cout << content;
}

int showCell(float content, const char* finalizer){
  initializeCell();
  cout << content << finalizer << endl;
}

int drawHorizontalLine(int length){
  cout.width(length);
  cout.fill('-');
  cout << '-' << endl;
  cout.fill(' ');
}

int showTableHead(){
  drawHorizontalLine(50);
  showCell("Size(Kb)");
  showCell("C lib");
  showCell("Win API");
  showCell("CopyFile", " |");
  drawHorizontalLine(50);
  return 0;
}

int main(){
  int size = 0;
  showTableHead();
  for (int i = 1; i < 10; i++){
    size = i*10000;
    createFile(size);
    showCell(size);
    showCell(getTimeExcecuting(copyByCLib,"data/file.dat","data/file1.dat"));
    showCell(getTimeExcecuting(copyByWin,"data/file.dat","data/file2.dat"));
    showCell(getTimeExcecuting(copyByCopyFile,"data/file.dat","data/file3.dat"), " |");
    drawHorizontalLine(50);
  }
}
