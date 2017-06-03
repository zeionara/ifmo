#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#define BUF_SIZE 256
using namespace std;

struct mark{
  char surname[10], discipline[40];
  int semester, mark;
};

mark* getMarks(){

  int length = 14;

  mark* marks = new mark[length];

  for (int i = 0; i < length; i++){
    strncpy(marks[i].surname, "Plyhin", sizeof(marks[i].surname));
    marks[i].mark = 5;
  }

  for (int i = 0; i < 4; i++){
    marks[i].semester = 1;
  }

  strncpy(marks[0].discipline, "Informatics", sizeof(marks[0].discipline));
  strncpy(marks[1].discipline, "Mathematics", sizeof(marks[1].discipline));
  strncpy(marks[2].discipline, "Programming basics", sizeof(marks[2].discipline));
  strncpy(marks[3].discipline, "Physics", sizeof(marks[3].discipline));
  marks[2].mark = 4;
  marks[3].mark = 3;

  for (int i = 4; i < 9; i++){
    marks[i].semester = 2;
  }

  strncpy(marks[4].discipline, "Discrete Mathematics", sizeof(marks[4].discipline));
  strncpy(marks[5].discipline, "Mathematics", sizeof(marks[5].discipline));
  strncpy(marks[6].discipline, "Basics of Computer Engeneering", sizeof(marks[6].discipline));
  strncpy(marks[7].discipline, "Basics of Programming", sizeof(marks[7].discipline));
  strncpy(marks[8].discipline, "Physics", sizeof(marks[8].discipline));

  for (int i = 9; i < 14; i++){
    marks[i].semester = 3;
  }

  strncpy(marks[9].discipline, "Computitional Mathematics", sizeof(marks[9].discipline));
  strncpy(marks[10].discipline, "Mathematics", sizeof(marks[10].discipline));
  strncpy(marks[11].discipline, "System programming software", sizeof(marks[11].discipline));
  strncpy(marks[12].discipline, "Languages of system programming", sizeof(marks[12].discipline));
  strncpy(marks[13].discipline, "Physics", sizeof(marks[13].discipline));

  return marks;
}

int saveMarks(const char* fileName, mark* marks){
  ofstream fout(fileName, ios::binary);
  for(int i = 0; i < 14; ++i)
  {
    fout.write((char *)(&marks[i]), sizeof(mark));
  }
  fout.close();
  return 0;
}

mark* loadMarks(const char* fileName){

  mark* marks = new mark[14];

  ifstream fin(fileName, ios::binary);
  for(int i = 0; i < 14; ++i)
  {
    fin.read((char *)(&marks[i]), sizeof(mark));
  }
  fin.close();
  return marks;
}

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

float getAverage(const char* fileName){
  mark* marks_loaded = loadMarks(fileName);

  int sum = 0;
  for (int i = 0; i < 14; i++){
    sum += marks_loaded[i].mark;
  }

  return (float)sum/14;
}

int main(){

  mark* marks = getMarks();

  saveMarks("data/data.dat", marks);

  if (copyByWin("data/data.dat","data/data_win_copied.dat")==0){
    cout << "Succesfully copied by Win API" << endl;
  } else {
    cout << "Error when copying by Win API" << endl;
  }

  if (copyByCLib("data/data.dat","data/data_c_copied.dat")==0){
    cout << "Succesfully copied by C lib" << endl;
  } else {
    cout << "Error when copying by C lib" << endl;
  }

  if (copyByCopyFile("data/data.dat", "data/data_copyfile_copied.dat")==0){
    cout << "Succesfully copied by Copy File" << endl;
  } else {
    cout << "Error when copying by CopyFile" << endl;
  }

  cout << "Average mark is "<<getAverage("data/data_c_copied.dat") << endl;

  return 0;
}
