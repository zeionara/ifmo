#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
using namespace std;
#define ID_MAX_LENGTH 32

typedef struct _treeNode{
  struct _treeNode *left, *right;
  char identifier[ID_MAX_LENGTH];
} TREENODE, *LPTNODE, **LPPTNODE;

#define NODE_SIZE sizeof(TREENODE)
#define NODE_HEAP_ISIZE 0x8000
#define ID_SIZE ID_MAX_LENGTH * sizeof(char)

LPTNODE FillTree (HANDLE, HANDLE, HANDLE);
BOOL Scan(LPTNODE, int);
//int KeyCompare(LPCTSTR, LPCTSTR);
BOOL InsertTree (LPPTNODE, LPTNODE);

int getHashTable(const char* fileName, HANDLE hNode){
    LPTNODE pRoot = NULL, pNode;
    char identifier[ID_MAX_LENGTH];

    ifstream identifiers(fileName);
    cout << fileName << endl;
    cout << identifiers << endl;
    if (identifiers == NULL){
      return 1;
    }

    while (identifiers){
      identifiers.getline(identifier, ID_MAX_LENGTH);
      pNode = (LPTNODE)HeapAlloc(hNode, HEAP_ZERO_MEMORY, NODE_SIZE);
      strncpy((*pNode).identifier,identifier,ID_SIZE);
      InsertTree(&pRoot, pNode);
      cout << (*pNode).identifier << endl;
    }
    int counter = 0;
    Scan(pRoot,counter);
}

int KeyCompare(const char* identifier1, const char* identifier2){
  return strcmp(identifier1, identifier2);
}

BOOL InsertTree(LPPTNODE ppRoot, LPTNODE pNode){
  if (*ppRoot == NULL){
    *ppRoot = pNode;
    return TRUE;
  }
  if (KeyCompare((*pNode).identifier,(*(*ppRoot)).identifier) < 0){
    InsertTree(&((*(*ppRoot)).left),pNode);
  } else {
    InsertTree(&((*(*ppRoot)).right),pNode);
  }
}

BOOL Scan(LPTNODE pNode,int counter){
  if (pNode == NULL){
    cout << endl;
    return true;
  }
  cout << pNode->identifier << endl;
  for (int i = 0; i < counter; i++){
    cout << " ";
  }

  cout << "Left subtree of " << pNode->identifier << " : ";
  Scan(pNode->left,counter+2);
  for (int i = 0; i < counter; i++){
    cout << " ";
  }
  cout << "Right subtree of " << pNode->identifier << " : ";
  Scan(pNode->right,counter+2);
  return true;
}

int main(int argc, char* argv[]){
  HANDLE hNode = NULL;
  LPTNODE pRoot;

  for (int i = 1; i < argc; i++){
    hNode = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, NODE_HEAP_ISIZE, 0);

    getHashTable(argv[1],hNode);

    if (hNode != NULL) HeapDestroy(hNode);
    hNode = NULL;
  }
  return 0;
}



/*LPTNODE FillTree (const char* fileName, HANDLE hNode, HANDLE hData){
  LPTNODE pRoot = NULL, pNode;
  DWORD nRead, i;
  BOOL AtCR;
  TCHAR DATA_HOLD[MAX_DATA_LEN];
  LPTSTR pString;
  char identifier[ID_MAX_LENGTH];

  ifstream identifiers(fileName);
  if (identifiers == NULL){
    return NULL;
  }
  while(identifiers){
    identifiers.getline(identifiers,ID_MAX_LENGTH);
    pNode = (LPTNODE)HeapAlloc(hNode, HEAP_ZERO_MEMORY, NODE_SIZE);

    strncpy((*pNode).identifier,identifier,ID_SIZE);
    cout << (*pNode).identifier << endl;
  }
  //while(TRUE){

    //ReadFile(hIn, pNode->Key, TKEY_SIZE, &nRead, NULL);

  //}
}*/
