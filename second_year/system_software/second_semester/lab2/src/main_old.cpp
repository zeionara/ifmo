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

typedef struct _treeNodeB{
  struct _treeNodeB *left, *right;
  char* identifier;
} treeNodeB, *treeNodeBPointer, **treeNodeBBasePointer;

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

char* getFullPointer(char* offset, char* base){
  return (char*)((int)offset + base);
  //return (char*)((DWORD)nodePointer->identifier + (DWORD)fileContent)
}

int KeyCompare(char* identifier1,char* identifier2, char* base){
  return strcmp(getFullPointer(identifier1,base), getFullPointer(identifier2,base));
}

BOOL InsertTree(treeNodeBBasePointer rootBasePointer, treeNodeBPointer nodePointer, char* fileContent){
  if (*rootBasePointer == NULL){
    *rootBasePointer = nodePointer;
    return TRUE;
  }
  if (KeyCompare(nodePointer->identifier,(*rootBasePointer)->identifier,fileContent) < 0){
    InsertTree(&((*rootBasePointer)->left),nodePointer,fileContent);
  } else {
    InsertTree(&((*rootBasePointer)->right),nodePointer,fileContent);
  }
}

treeNodePointer fillTreeHeap(const char* fileName, HANDLE hNode){
    treeNodePointer rootPointer = NULL, nodePointer;
    char identifier[ID_MAX_LENGTH];
    ifstream identifiers(fileName);
    if (identifiers == NULL){
      return NULL;
    }
    while (identifiers){
      identifiers.getline(identifier, ID_MAX_LENGTH);
      nodePointer = (treeNodePointer)HeapAlloc(hNode, HEAP_ZERO_MEMORY, NODE_SIZE);
      strncpy(nodePointer->identifier,identifier,ID_SIZE);
      InsertTree(&rootPointer, nodePointer);
    }
    return rootPointer;
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

treeNodePointer fillTreeMMF(const char* fileName, HANDLE hNode, LPVOID mappedFile,DWORD fileSize){
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

treeNodeBPointer fillTreeBases(const char* fileName, HANDLE hNode, LPVOID mappedFile,DWORD fileSize){
    treeNodeBPointer rootPointer = NULL, nodePointer;
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
      nodePointer = (treeNodeBPointer)HeapAlloc(hNode, HEAP_ZERO_MEMORY, NODE_SIZE);
      fileContent[pos] = '\0';
      nodePointer->identifier = (char*)old_pos;
      //cout << "We have new identifier : " << getFullPointer(nodePointer->identifier,fileContent) << endl;
      //fileContent[pos] = '\n';
      InsertTree(&rootPointer, nodePointer, fileContent);
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
  cout << nodePointer->identifier << endl;
  for (int i = 0; i < counter; i++){
    cout << "|  ";
  }
  cout << "|---Left subtree of " << nodePointer->identifier << " : ";
  Scan(nodePointer->left,counter+2);
  for (int i = 0; i < counter; i++){
    cout << "|  ";
  }
  cout << "|---Right subtree of " << nodePointer->identifier << " : ";
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

int initializeCell(){
  cout << "| ";
  cout.setf(ios::left);
  cout.width(30);
  return 0;
}

int drawHorizontalLine(int length){
  cout.width(length);
  cout.fill('-');
  cout << '-' << endl;
  cout.fill(' ');
}

int showCell(const char* content, const char* finalizer){
  initializeCell();
  cout << content << finalizer << endl;
}

int showCell(const char* content){
  initializeCell();
  cout << content;
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

int showTableHead(){
  drawHorizontalLine(130);
  showCell("Size (Mb)");
  showCell("Only Heap ");
  showCell("Heap + MMF ");
  showCell("Heap + MMF + Based pointers", " |");
  drawHorizontalLine(130);
  return 0;
}

int main(int argc, char* argv[]){
  cout << "Test creating binary tree from the data in external file (time in seconds):" << endl;
  HANDLE hNode = NULL;
  treeNodePointer rootPointer;
  int numberOfIdentifiers = 0;

  HANDLE hFile = INVALID_HANDLE_VALUE, hMap = NULL;
  LPVOID pFile = NULL;
  LPVOID mappedFile = NULL;
  DWORD FsLow, Result = 2;
  DWORD oop;

  if (argc != 2){
    cout << "Usage : heaps path/to/file" << endl;
  }
  showTableHead();
  float tmp;
  for (int i = 1; i <= 10; i++){
    //heap
    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);
    numberOfIdentifiers = i*100000;
    //hFile = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    generateFile(numberOfIdentifiers,argv[1],3,32);
    float fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    rootPointer = fillTreeHeap(argv[1],hNode);
    float fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    //cout << "In heap tree containing " << numberOfIdentifiers << " elements was filled in " << fTimeStop - fTimeStart << " secs " << endl;
    tmp = fTimeStop - fTimeStart;
    if (hNode != NULL) HeapDestroy(hNode);
    hNode = NULL;

    //MMF
    hFile = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    DWORD fileSize = GetFileSize(hFile,&oop);
    showCell((float)fileSize/1048576);
    showCell(tmp);
    hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);
    mappedFile = MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,0,0,fileSize);

    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);

    fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    rootPointer = fillTreeMMF(argv[1],hNode,mappedFile,fileSize);
    fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    //cout << "In heap tree containing " << numberOfIdentifiers << " elements with using MMF was filled in " << fTimeStop - fTimeStart << " secs " << endl;
    showCell(fTimeStop - fTimeStart);
    UnmapViewOfFile(mappedFile);
    CloseHandle(hMap);
    CloseHandle(hFile);
    if (hNode != NULL) HeapDestroy(hNode);
    hNode = NULL;

    //bases
    hFile = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    fileSize = GetFileSize(hFile,&oop);
    hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);
    mappedFile = MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,0,0,fileSize);

    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);

    fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    treeNodeBPointer ootPointer = fillTreeBases(argv[1],hNode,mappedFile,fileSize);
    fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    //cout << "In heap tree containing " << numberOfIdentifiers << " elements with using MMF and based pointers was filled in " << fTimeStop - fTimeStart << " secs " << endl;
    showCell(fTimeStop - fTimeStart," |");
    UnmapViewOfFile(mappedFile);
    CloseHandle(hMap);
    CloseHandle(hFile);
    if (hNode != NULL) HeapDestroy(hNode);
    hNode = NULL;
    drawHorizontalLine(130);
  }
  int counter = 0;
  return 0;
}
