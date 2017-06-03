#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;
#define ID_MAX_LENGTH 32

typedef struct _treeNode{
  struct _treeNode *left, *right;
  char identifier[ID_MAX_LENGTH];
} treeNode, *treeNodePointer, **treeNodeBasePointer;

#define NODE_SIZE sizeof(treeNode)
#define NODE_HEAP_ISIZE 0x8000
#define ID_SIZE ID_MAX_LENGTH * sizeof(char)

int KeyCompare(const char* identifier1, const char* identifier2){
  return strcmp(identifier1, identifier2);
}

BOOL InsertTree(treeNodeBasePointer rootBasePointer, treeNodePointer nodePointer){
  if (*rootBasePointer == NULL){
    *rootBasePointer = nodePointer;
    return TRUE;
  }
  if (KeyCompare(nodePointer->identifier,(*rootBasePointer)->identifier) < 0){
    InsertTree(&((*rootBasePointer)->left),nodePointer);
  } else {
    InsertTree(&((*rootBasePointer)->right),nodePointer);
  }
}

DWORD find(const char* string, char rc, DWORD start, DWORD maxindex){
  char c = '\0';
  DWORD index = start;
  DWORD counter = 0;
  do{
    if (index >= maxindex){
      break;
    }
    c = string[index];
    if (c == rc){
      return index;
    }
    index++;
  } while(true);
  return 0;
}

treeNodePointer fillTree(const char* fileName, HANDLE hNode, LPVOID mappedFile,DWORD fileSize){
    treeNodePointer rootPointer = NULL, nodePointer;
    //char identifier[ID_MAX_LENGTH];
    //ifstream identifiers(fileName);
    //if (identifiers == NULL){
    //  return NULL;
    //}

    char* fileContent = (char*)mappedFile;

    DWORD old_pos = 0;
    DWORD pos = -1;
    char identifier[32];
    DWORD i = 1;
    while(true){
      old_pos = pos+1;
      pos = find(fileContent, '\n', old_pos, fileSize);
      if (pos == 0) {
        break;
      }
      nodePointer = (treeNodePointer)HeapAlloc(hNode, HEAP_ZERO_MEMORY, NODE_SIZE);
      fileContent[pos] = '\0';
      strncpy(nodePointer->identifier,fileContent+old_pos,ID_SIZE);
      //cout << "We have new identifier : " << nodePointer->identifier << endl;
      fileContent[pos] = '\n';
      InsertTree(&rootPointer, nodePointer);
      i++;
    }

    /*while (identifiers){
      identifiers.getline(identifier, ID_MAX_LENGTH);
      nodePointer = (treeNodePointer)HeapAlloc(hNode, HEAP_ZERO_MEMORY, NODE_SIZE);
      strncpy(nodePointer->identifier,identifier,ID_SIZE);
      InsertTree(&rootPointer, nodePointer);
    }*/
    return rootPointer;
}

BOOL Scan(treeNodePointer nodePointer,int counter){
  if (nodePointer == NULL){
    cout << endl;
    return true;
  }
  for (int i = 0; i < counter; i++){
    cout << "  ";
  }
  cout << nodePointer->identifier << endl;
  Scan(nodePointer->left,counter+2);
  Scan(nodePointer->right,counter+2);
  return true;
}

int generateFile(int numberOfIdentifiers, const char* fileName, int minlength, int maxlength){
    int length = 0;
    srand(time(NULL));
    FILE* identifiers = fopen(fileName,"w");
    if (identifiers == NULL){
      return 1;
    }
    for (int i = 0; i < numberOfIdentifiers; i++){
      length = rand() % (maxlength - minlength) + minlength;
      char identifier[length + 1];
      identifier[length] = '\0';
      for (int j = 0; j < length; j++){
        identifier[j] = (char)( rand() % 24 + 99);
      }
      fprintf(identifiers, "%s\n", identifier);
    }
    fclose(identifiers);
    return 0;
}

int main(int argc, char* argv[]){
  HANDLE hNode = NULL;
  treeNodePointer rootPointer;

  HANDLE hFile = INVALID_HANDLE_VALUE, hMap = NULL;
  LPVOID pFile = NULL;
  LPVOID mappedFile = NULL;
  DWORD FsLow, Result = 2;
  int numberOfIdentifiers = 0;
  DWORD oop;

  for (int i = 1; i <= 10; i++){
    numberOfIdentifiers = i*100000;
    generateFile(numberOfIdentifiers,argv[1],3,32);
    hFile = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    DWORD fileSize = GetFileSize(hFile,&oop);

    hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);
    mappedFile = MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,0,0,fileSize);

    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);

    float fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    rootPointer = fillTree(argv[1],hNode,mappedFile,fileSize);
    float fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    cout << "In heap tree containing " << numberOfIdentifiers << " elements with using MMF was filled in " << fTimeStop - fTimeStart << " secs " << endl;

    UnmapViewOfFile(mappedFile);
    CloseHandle(hMap);
    CloseHandle(hFile);
    if (hNode != NULL) HeapDestroy(hNode);
    hNode = NULL;
  }

  /*HANDLE hNode = NULL;
  treeNodePointer rootPointer;
  int numberOfIdentifiers = 0;
  if (argc != 2){
    cout << "Usage : heaps path/to/file" << endl;
  }
  for (int i = 1; i < 10; i++){
    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);
    numberOfIdentifiers = i*100000;
    generateFile(numberOfIdentifiers,argv[1],3,32);
    float fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    rootPointer = fillTree(argv[1],hNode);
    float fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    cout << "In heap tree containing " << numberOfIdentifiers << " elements was filled in " << fTimeStop - fTimeStart << " secs " << endl;
    if (hNode != NULL) HeapDestroy(hNode);
    hNode = NULL;
  }
  int counter = 0;
  return 0;*/
}
