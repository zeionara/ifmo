#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;

#define PATH_MAX_LEN 256
#define KEY_SIZE 8
#define DATA_LEN 32
#define IDX_ENTRY_SIZE KEY_SIZE + sizeof(DWORD)

typedef struct _record{
  char key[KEY_SIZE];
  char data[DATA_LEN];
} record;

#define RECORD_SIZE sizeof(record)

#define ID_MAX_LENGTH 32

typedef struct _treeNode{
  struct _treeNode *left, *right;
  char identifier[ID_MAX_LENGTH];
} treeNode, *treeNodePointer, **treeNodeBasePointer;

typedef struct _treeNodeB{
  struct _treeNodeB *left, *right;
  DWORD identifier;
} treeNodeB, *treeNodeBPointer, **treeNodeBBasePointer;

#define NODE_SIZE sizeof(treeNode)
#define NODEB_SIZE sizeof(treeNodeB)
#define NODE_HEAP_ISIZE 0x8000
#define ID_SIZE ID_MAX_LENGTH * sizeof(char)

int KeyCompare(const void* identifier1, const void* identifier2){
  return strcmp((char*)identifier1, (char*)identifier2);
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
/*char* getFullPointer(DWORD offset, char* base){
  return (offset + base);
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

BOOL InsertTree(treeNodeBBasePointer rootBasePointer, treeNodeBPointer nodePointer, char* base){
  if (*rootBasePointer == NULL){
    *rootBasePointer = nodePointer;
    return TRUE;
  }
  if (KeyCompare(nodePointer->identifier,(*rootBasePointer)->identifier,base) < 0){
    InsertTree(&((*rootBasePointer)->left),nodePointer,base);
  } else {
    InsertTree(&((*rootBasePointer)->right),nodePointer,base);
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

treeNodePointer fillTreeMMF(const char* fileName, HANDLE hNode, LPVOID mappedFile,DWORD fileSize){
    treeNodePointer rootPointer = NULL, nodePointer;
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
      fileContent[pos] = '\n';
      InsertTree(&rootPointer, nodePointer);
      i++;
    }
    return rootPointer;
}

treeNodeBPointer fillTreeBases(const char* fileName, HANDLE hNode, LPVOID mappedFile,DWORD fileSize){
    treeNodeBPointer rootPointer = NULL, nodePointer;
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
      nodePointer = (treeNodeBPointer)HeapAlloc(hNode, HEAP_ZERO_MEMORY, NODEB_SIZE);
      fileContent[pos] = '\0';
      nodePointer->identifier = old_pos;
      InsertTree(&rootPointer, nodePointer, fileContent);
      i++;
    }
    return rootPointer;
}*/

int generateFile(int numberOfIdentifiers, const char* fileName, int length){
    srand(time(NULL));
    FILE* identifiers = fopen(fileName,"w");
    if (identifiers == NULL){
      return 1;
    }
    for (int i = 0; i < numberOfIdentifiers; i++){
      char identifier[length + 1];
      identifier[length] = '\0';
      for (int j = 0; j < length; j++){
        identifier[j] = (char)( rand() % 24 + 99);
      }
      fprintf(identifiers, "%s ", identifier);
    }
    fclose(identifiers);
    return 0;
}


int generateFileEx(int numberOfIdentifiers, const char* fileName, int minlength, int maxlength){
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
  showCell("Heap ");
  showCell("MMF ");
  showCell("Heap + MMF + Based pointers", " |");
  drawHorizontalLine(130);
  return 0;
}

/*DWORD CreateIndexFile(DWORD fileSize, const char* idxFileName, LPVOID mappedFile){
  HANDLE hXFile;
  char __based(mappedFile) *mappedFileFragment;
  DWORD nWrite, KStart, KSize;

  hXFile = CreateFile(idxFileName,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,0,NULL);
  KStart = (DWORD) mappedFileFragment;
  while(*mappedFileFragment != TSPACE && *mappedFileFragment != TAB) mappedFileFragment++;
  KSize = ((DWORD)mappedFileFragment - KStart);

}*/

int main(int argc, char* argv[]){
  cout << "Test sorting external file (time in seconds):" << endl;

  HANDLE hHeap = NULL;
  treeNodePointer rootPointer;
  int numberOfIdentifiers = 0;
  DWORD fileSize;
  DWORD KStart, KSize;

  HANDLE hFile = INVALID_HANDLE_VALUE, hMap = NULL;
  LPVOID pFile = NULL;
  LPVOID mappedFile = NULL, mappedXFile = NULL;
  DWORD * pSizes;
  float tmp;

  char tmpFileName[PATH_MAX_LEN];
  char idxFileName[PATH_MAX_LEN];
  strncpy(tmpFileName,argv[1],PATH_MAX_LEN);
  strcat(tmpFileName,".sorted");

  strncpy(idxFileName,argv[1],PATH_MAX_LEN);
  strcat(idxFileName,".idx");

  //showTableHead();
  for (int i = 1; i <= 1; i++){
    //generateFile(i*100,argv[1],RECORD_SIZE-1);
    //Heap
    /*CopyFile(argv[1],tmpFileName,TRUE);
    hFile = CreateFile(tmpFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    fileSize = GetFileSize(hFile,NULL);
    showCell((float)fileSize/1048576);
    CloseHandle(hFile);
    float fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);

    char* identifier = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,fileSize);
    ifstream identifiers(tmpFileName);
    if (identifiers == NULL){
      return 1;
    }
    identifiers.read(identifier,fileSize);
    identifiers.close();

    qsort(identifier,fileSize/RECORD_SIZE,RECORD_SIZE,KeyCompare);

    ofstream outfile(tmpFileName);
    if (outfile == NULL){
      return 1;
    }
    outfile.write(identifier,fileSize);
    outfile.close();
    float fTimeStop = clock()/(float)CLOCKS_PER_SEC;

    showCell(fTimeStop - fTimeStart);

    if (hHeap != NULL) HeapDestroy(hHeap);
    hHeap = NULL;
    DeleteFile(tmpFileName);

    //MMF
    CopyFile(argv[1],tmpFileName,TRUE);
    fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    hFile = CreateFile(tmpFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
    mappedFile = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    qsort(mappedFile,fileSize/RECORD_SIZE,RECORD_SIZE,KeyCompare);

    UnmapViewOfFile(mappedFile);
    CloseHandle(hMap);
    CloseHandle(hFile);
    fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    showCell(fTimeStop - fTimeStart);*/

    //Based
    //showCell(22," |");
    //drawHorizontalLine(130);

    //DeleteFile(tmpFileName);

    //Based pointers
    generateFileEx(i*10,argv[1],32,64);
    CopyFile(argv[1],tmpFileName,TRUE);
    //hFile = CreateFile(tmpFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    HANDLE hInFile, hInMap;
    HANDLE hXFile, hXMap;
    hInFile = CreateFile(tmpFileName,GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, 0, NULL);
    fileSize = GetFileSize(hInFile,NULL);
    hInMap = CreateFileMapping(hInFile,NULL,PAGE_READWRITE,0,0,NULL);
    mappedFile = MapViewOfFile(hInMap,FILE_MAP_ALL_ACCESS,0,0,0);
    char* fileContent = (char*)mappedFile;


    hXFile = CreateFile(idxFileName,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,0,NULL);
    DWORD es = IDX_ENTRY_SIZE;
    DWORD xFileSize = 10*es;
    //cout << xFileSize << endl;
    hXMap = CreateFileMapping(hXFile,NULL,PAGE_READWRITE,0,xFileSize,NULL);
    mappedXFile = MapViewOfFile(hXMap,FILE_MAP_ALL_ACCESS,0,0,xFileSize);

    char* xfileContent = (char*)mappedXFile;
    //hXFile = CreateFile(argv[1],GENERIC_READ | GENERIC_WRITE, 0, NULL, ALWAYS_CREATE, 0, NULL);
    //hXMap = CreateFileMapping(hXFile,NULL,PAGE_READWRITE,0,0,NULL);
    //mappedXFile = MapViewOfFile(hXMap,FILE_MAP_ALL_ACCESS,0,0,0);

    DWORD basedDataPointer = 0;

    DWORD old_pos = 0;
    DWORD pos = -1;
    char key[8];
    char tmp;
    //DWORD j = 0;
    while(true){
      old_pos = pos+1;
      pos = find(fileContent, '\n', old_pos, fileSize);
      //cout << fileSize << endl;
      if (pos == 0) {
        break;
      }
      //nodePointer = (treeNodePointer)HeapAlloc(hNode, HEAP_ZERO_MEMORY, NODE_SIZE);
      //fileContent[old_pos+8] = '\0';
      strncpy(key,fileContent+old_pos,8);
      strncpy(xfileContent,key,8);
      xfileContent+=8;
      strncpy(xfileContent,(char*)(&old_pos),4);
      xfileContent+=4;
      //key[8] = '\0';
      cout << key << endl;
      cout << old_pos << endl;
      cout << sizeof(key)+sizeof(old_pos) << endl;
      //fileContent[pos] = '\n';
      //InsertTree(&rootPointer, nodePointer);
      //j++;
    }
    cout << IDX_ENTRY_SIZE << endl;

    cout << (char*)mappedXFile << endl;

    xfileContent = (char*)mappedXFile;
    strncpy(key,xfileContent,8);
    DWORD point = *((DWORD*)(xfileContent+8+4+8+4+8+4+8));
    cout << point << endl;

    UnmapViewOfFile(mappedFile);
    CloseHandle(hInMap);
    CloseHandle(hInFile);
    UnmapViewOfFile(mappedXFile);
    CloseHandle(hXMap);
    CloseHandle(hXFile);


    hFile = CreateFile(idxFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
    mappedFile = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

    qsort(mappedFile,xFileSize/es,es,KeyCompare);

    UnmapViewOfFile(mappedFile);
    CloseHandle(hMap);
    CloseHandle(hFile);

    //pSizes = (LPDWORD)mappedXFile;
    //KSize = *pSizes;
    //KStart = *(pSizes + 1);


  }
  return 0;
  /*if (argc != 2){
    cout << "Usage : heaps path/to/file" << endl;
  }
  showTableHead();
  for (int i = 1; i <= 10; i++){
    numberOfIdentifiers = i*100000;
    generateFile(numberOfIdentifiers,argv[1],3,32);

    //heap
    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);

    float fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    rootPointer = fillTreeHeap(argv[1],hNode);
    float fTimeStop = clock()/(float)CLOCKS_PER_SEC;
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

    fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    rootPointer = fillTreeMMF(argv[1],hNode,mappedFile,fileSize);
    fTimeStop = clock()/(float)CLOCKS_PER_SEC;

    showCell(fTimeStop - fTimeStart);
    UnmapViewOfFile(mappedFile);
    CloseHandle(hMap);
    CloseHandle(hFile);
    if (hNode != NULL) HeapDestroy(hNode);
    hNode = NULL;

    //bases
    hFile = CreateFile(argv[1], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);
    mappedFile = MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,0,0,fileSize);

    fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    treeNodeBPointer rootPointer = fillTreeBases(argv[1],hNode,mappedFile,fileSize);
    fTimeStop = clock()/(float)CLOCKS_PER_SEC;

    showCell(fTimeStop - fTimeStart," |");
    UnmapViewOfFile(mappedFile);
    CloseHandle(hMap);
    CloseHandle(hFile);
    if (hNode != NULL) HeapDestroy(hNode);
    hNode = NULL;
    drawHorizontalLine(130);
  }*/
  int counter = 0;
  return 0;
}
