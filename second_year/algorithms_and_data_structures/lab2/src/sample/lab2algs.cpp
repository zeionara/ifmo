#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <windows.h>
using namespace std;

struct node{
  char name[32];
  char key[32];
};

DWORD getFirstChildIndex(node* heap, DWORD d, DWORD i, DWORD n){
  DWORD k = d * i + 1;
  if (k > n) return 0;
  return k;
}

DWORD getLastChildIndex(node* heap, DWORD d, DWORD i, DWORD n){
  DWORD k = getFirstChildIndex(heap, d, i, n);
  return n > k+d-1 ? k+d-1 : n;
}

int main(){
  node* heap;
  heap = (struct node *)malloc(sizeof(node));
  strcpy(heap[0].name,strcat("Vi",1));
  strcpy(heap[0].name,"Coop");
  heap += sizeof(node);
  heap = (struct node *)malloc(sizeof(node));
}
