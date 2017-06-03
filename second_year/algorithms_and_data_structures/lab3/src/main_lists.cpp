#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

#define HEAP_SIZE_DEFAULT 0x8000

//
//
//Disjoint Set
//
//

typedef struct _DisjointSetObject DisjointSetObject, *DisjointSetObjectPointer;

typedef struct _DisjointSetObject{
  DisjointSetObjectPointer representator;
  DisjointSetObjectPointer last;
  unsigned int size;
  unsigned int value;
  DisjointSetObjectPointer next;
} DisjointSetObject, *DisjointSetObjectPointer;

DisjointSetObjectPointer makeSet(unsigned int x){
  DisjointSetObjectPointer newSet = (DisjointSetObjectPointer)malloc(sizeof(DisjointSetObject));
  newSet->representator = newSet;
  newSet->size = 1;
  newSet->last = newSet;
  newSet->next = NULL;
  newSet->value = x;
  return newSet;
}

DisjointSetObjectPointer findSet(DisjointSetObjectPointer x){
  return x->representator;
}

int showDisjointSet(DisjointSetObjectPointer set){
  cout << "Set : ";
  DisjointSetObjectPointer current = set;
  for (int i = 0; i < set->size; i++){
    cout << " " << current->value << " ";
    current = current->next;
  }
  cout << endl;
  return 0;
}

DisjointSetObjectPointer makeUnion(DisjointSetObjectPointer x, DisjointSetObjectPointer y){
  DisjointSetObjectPointer first;
  DisjointSetObjectPointer second;
  DisjointSetObjectPointer current;
  if (x->size >= y->size){
    first = x->representator;
    second = y->representator;
  } else {
    first = y->representator;
    second = x->representator;
  }
  current = first->last;
  first->last->next = second;
  first->last = second->last;
  first->size = first->size + second->size;
  do{
    current->representator = first;
    current = current->next;
  } while(current != first->last);
  return first;
}

//
//
//Boruvka
//
//

//
//
//Prim
//
//


int main(int argc, char* argv[]){
  DisjointSetObjectPointer set1 = makeSet(66);
  DisjointSetObjectPointer set2 = makeSet(67);
  DisjointSetObjectPointer set3 = makeSet(68);
  DisjointSetObjectPointer set4 = makeSet(69);
  set1 = makeUnion(set1, set2);
  set3 = makeUnion(set3, set4);
  set1 = makeUnion(set1, set3);
  showDisjointSet(set1);
  cout << "OK" << endl;
}
