#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <ctime>
using namespace std;

struct hashTableEntry{
  char identifier[32];
  hashTableEntry* next;
};

int getHashCode(const char* identifier){
  return (int(identifier[0]) + int(identifier[1]) + int(identifier[strlen(identifier)-1]));
}

int getSumEx(int number){
  int sum = 0;
  for (int i = 1; i <= number; i++){
    sum+=i;
  };
  return sum;
}

hashTableEntry* getHashTable(const char* fileName, int size, int maxlength){
    char identifier[maxlength];
    hashTableEntry* hashTable = new hashTableEntry[size];
    int* numOfCollisions = new int[size];
    int counter = 0;

    for (int i = 0; i < size; i++){
      numOfCollisions[i] = 0;
      hashTable[i].next = 0;
    }
    ifstream identifiers(fileName);

    if (identifiers == NULL){
      return NULL;
    }
    int numOfElements = 0;
    while (identifiers){
      identifiers.getline(identifier, maxlength);
      numOfElements++;
      hashTableEntry* tableEntry = &hashTable[getHashCode(identifier)];
      while ((*tableEntry).next != 0){
        tableEntry = (*tableEntry).next;
      }

      if ((*tableEntry).next == 0){
        if (numOfCollisions[getHashCode(identifier)] == 0){
          counter++;
        }
        numOfCollisions[getHashCode(identifier)]++;
        hashTableEntry *entry = new hashTableEntry;
        (*entry).next = 0;

        (*tableEntry).next = entry;
        strncpy((*tableEntry).identifier,identifier,sizeof((*tableEntry).identifier));
      }
    }

    int sum = 0;
    int bigsum = 0;
    for (int i = 0; i < size; i++){
      sum += numOfCollisions[i];
      bigsum += getSumEx(numOfCollisions[i]);
    }

    cout << "Average number of collisions : " << sum/counter << endl;
    cout << "Average number of compares : " << bigsum/numOfElements << endl;
    return hashTable;
}



hashTableEntry* searchEntry(const char* identifier, hashTableEntry* hashTable){
  int counter = 1;
  hashTableEntry* tableEntry = &hashTable[getHashCode(identifier)];
  while ((strcmp((*tableEntry).identifier,identifier) != 0) && ((*tableEntry).next != 0)){
    counter++;
    tableEntry = (*tableEntry).next;
  }
  if ((*tableEntry).next == 0){
    cout << "Not found" << endl;
    return 0;
  }
  cout << "Done " << counter << " compares " << endl;
  return tableEntry;
}

int main(int argc, char* argv[]){
  const char* quitstr = "quit";
  if (argc != 2){
    cout << "Usage : filehash path/to/file" << endl;
    return 0;
  }
  hashTableEntry* hashTable = getHashTable(argv[1],367,32);
  hashTableEntry* tableEntry; //= searchEntry("piczrfxk", hashTable;
  string identifier;
  cout << "To search identifier enter identifier. To quit enter \'" << quitstr << "\'" << endl;
  cin >> identifier;
  while (strcmp(identifier.c_str(),"quit") != 0){
    tableEntry = searchEntry(identifier.c_str(), hashTable);
    cin >> identifier;
  }
  cout << "See you soon!" << endl;
}
