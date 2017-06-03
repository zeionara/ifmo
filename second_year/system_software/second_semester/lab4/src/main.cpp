#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
using namespace std;

#define PATH_MAX_LEN 256
#define HEAP_SIZE_DEFAULT 0x8000

typedef struct _SENTENCE{
  char* pointer;
  DWORD length;
} SENTENCE, *PSENTENCE;

#define SENTENCESIZE sizeof(SENTENCE)

int replaceSpaces(char* text, DWORD textSize){
  for(int i = 0; i < textSize; i++){
    if (isspace(*(text+i))){
      *(text+i) = ' ';
    }
  }
}

bool check(const char* array, const char* searched){
    for (DWORD i = 0; i < strlen(searched); i++){
        if (array[i] != searched[i]){
          return false;
        }
    }
    return true;
}

bool showSentence(char* text, DWORD max_forward, DWORD max_backward){
  for (DWORD i = 0; i < PATH_MAX_LEN; i++){
    if ((i >= max_forward) || (*(text + i) == '.') || (*(text + i) == '!') || (*(text + i) == '?')){
      *(text + i + 1) = 0;
      for (int j = 0; j < PATH_MAX_LEN; j++){
        if (((j) >= max_backward) || (*(text - j) == '.') || (*(text - j) == '!') || (*(text - j) == '?')){
          if (j >= max_backward){
            cout << (text - j) << endl;
          } else {
            cout << (text - j + 1) << endl;
          }

          *(text + i + 1) = '.';
          return true;
        }
      }
      cout << text - PATH_MAX_LEN << endl;
      *(text + i) = '.';
      return true;
    }
  }
  return false;
}

DWORD getNumOfSentences(char* text, DWORD textSize){

  DWORD counter = 0;
  //cout << text << endl;
  for (DWORD i = 0; i < textSize; i++){

    if ((*(text + i) == '.') || (*(text + i) == '!') || (*(text + i) == '?')){
      counter++;
    }
  }
  return counter;
}

DWORD getSentenceLength(char* startOfSentence){
  DWORD i = 0;
  char c = ' ';
  do{
    c = *(startOfSentence + i);
    i++;
  }while((c!='.') && (c!='!') && (c!='?'));
  //cout << i << endl;
  return i;
}

int Compare(const void* sent1, const void* sent2){
  PSENTENCE firstsentence = (PSENTENCE)sent1;
  PSENTENCE secondsentence = (PSENTENCE)sent2;

  char* endOfFirstIndex = firstsentence->pointer+firstsentence->length;
  char endOfFirstChar = *(endOfFirstIndex);

  char* endOfSecIndex = secondsentence->pointer+secondsentence->length;
  char endOfSecChar = *(endOfSecIndex);

  *(endOfFirstIndex) = 0;
  *(endOfSecIndex) = 0;

  int result = strcmp(firstsentence->pointer, secondsentence->pointer);

  *(endOfFirstIndex) = endOfFirstChar;
  *(endOfSecIndex) = endOfSecChar;

  return result;
}

int CompareDesc(const void* sent1, const void* sent2){
  PSENTENCE firstsentence = (PSENTENCE)sent1;
  PSENTENCE secondsentence = (PSENTENCE)sent2;

  char* endOfFirstIndex = firstsentence->pointer+firstsentence->length;
  char endOfFirstChar = *(endOfFirstIndex);

  char* endOfSecIndex = secondsentence->pointer+secondsentence->length;
  char endOfSecChar = *(endOfSecIndex);

  *(endOfFirstIndex) = 0;
  *(endOfSecIndex) = 0;

  int result = (-1)*strcmp(firstsentence->pointer, secondsentence->pointer);

  *(endOfFirstIndex) = endOfFirstChar;
  *(endOfSecIndex) = endOfSecChar;

  return result;
}

void showSentence(PSENTENCE sent){
  char* endOfSentence = sent->pointer+sent->length;
  char endOfSentenceChar = *(endOfSentence);

  *(endOfSentence) = 0;

  cout << sent->pointer << endl;

  *(endOfSentence) = endOfSentenceChar;
}

int sort(const char* fileName, const char* sortTemplate){
  char sortedFileName[PATH_MAX_LEN];
  strncpy(sortedFileName,fileName,PATH_MAX_LEN);
  strcat(sortedFileName,".srtd");

  CopyFile(fileName, sortedFileName, FALSE);
  HANDLE hFile = CreateFile(fileName,GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  DWORD fileSize = GetFileSize(hFile,NULL);
  HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
  char* mappedFile = (char*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, fileSize);
  //replaceSpaces(mappedFile,fileSize);
  char* mappedFileNull = mappedFile;
  HANDLE hSentencesHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, HEAP_SIZE_DEFAULT, 0);

  DWORD numOfSentences =  getNumOfSentences(mappedFile, fileSize);
  PSENTENCE sentences = (PSENTENCE)HeapAlloc(hSentencesHeap, HEAP_ZERO_MEMORY, numOfSentences*sizeof(SENTENCE));
  DWORD index = 0;
  DWORD accumulator = 0;
  for (int i = 0; i < numOfSentences; i++){
    (sentences+i)->pointer = mappedFile + accumulator;
    (sentences+i)->length = getSentenceLength(mappedFile + accumulator);
    accumulator += (sentences+i)->length;
  }

  if (strcmp(sortTemplate,"asc")==0){
    qsort(sentences, numOfSentences, sizeof(SENTENCE), Compare);
  } else if (strcmp(sortTemplate,"desc")==0){
    qsort(sentences, numOfSentences, sizeof(SENTENCE), CompareDesc);
  }


  HANDLE hFileS = CreateFile(sortedFileName,GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  DWORD fileSizeS = GetFileSize(hFileS,NULL);
  HANDLE hMapS = CreateFileMapping(hFileS, NULL, PAGE_READWRITE, 0, fileSizeS, NULL);
  char* mappedFileS = (char*)MapViewOfFile(hMapS, FILE_MAP_ALL_ACCESS, 0, 0, fileSizeS);
  char* mappedFileNullS = mappedFileS;

  accumulator = 0;
  for (int i = 0; i < numOfSentences; i++){
    strncpy(mappedFileS+accumulator,(sentences+i)->pointer,(sentences+i)->length);
    accumulator += (sentences+i)->length;
  }

  UnmapViewOfFile(mappedFileS);
  CloseHandle(hMapS);
  CloseHandle(hFileS);

  UnmapViewOfFile(mappedFile);
  CloseHandle(hMap);
  CloseHandle(hFile);

  return 0;
}

int search(const char* fileName, const char* searched){
  char tmpFileName[PATH_MAX_LEN];
  strncpy(tmpFileName,fileName,PATH_MAX_LEN);
  strcat(tmpFileName,".tmp");
  DWORD searchedLen = strlen(searched);

  CopyFile(fileName, tmpFileName, FALSE);

  HANDLE hFile = CreateFile(tmpFileName,GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
  DWORD fileSize = GetFileSize(hFile,NULL);
  HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
  char* mappedFile = (char*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, fileSize);
  char* mappedFileNull = mappedFile;

  mappedFile[fileSize - 1] = 0;
  for (DWORD i = 0; i < fileSize; i++){
    if (check(mappedFile+i,searched)){
      showSentence(mappedFile+i,fileSize-i-1,i);
      i += searchedLen - 1;
    }
  }
  UnmapViewOfFile(mappedFile);
  CloseHandle(hMap);
  CloseHandle(hFile);
  return 0;
}

int main(int argc, char* argv[]){
  setlocale(LC_ALL,"Russian");
  if (argc != 5){
    cout << "Usage : main name_of_file_for_sorting template_for_sorting name_of_file_for_searching str_for_searching" << endl;
    return 1;
  }
  sort(argv[1],argv[2]);
  search(argv[3],argv[4]);
}
