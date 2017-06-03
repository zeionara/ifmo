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

int getHashCode(const char* identifier){
  return (int(identifier[0]) + int(identifier[1]) + int(identifier[strlen(identifier)-1]));
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

    while (identifiers){
      identifiers.getline(identifier, maxlength);
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
        //cout << "New entry's next : " << (*entry).next << endl;

        (*tableEntry).next = entry;
        strncpy((*tableEntry).identifier,identifier,sizeof((*tableEntry).identifier));
      }
    }
    int sum = 0;
    for (int i = 0; i < size; i++){
      cout << numOfCollisions[i] << endl;
      sum += numOfCollisions[i];
    }

    cout << "Average number of collisions (compares to find element): " << (float)sum/counter << endl;
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

int main(){
  const char* quitstr = "quit";
  //generateFile(100000, "data/identifiers.dat", 3, 32);
  hashTableEntry* hashTable = getHashTable("data/identifiers.dat",367,32);
  hashTableEntry* tableEntry; //= searchEntry("piczrfxk", hashTable;
  string identifier;
  cout << "To quit enter \'" << quitstr << "\'" << endl;
  cin >> identifier;
  while (strcmp(identifier.c_str(),"quit") != 0){
    tableEntry = searchEntry(identifier.c_str(), hashTable);
    cin >> identifier;
  }
  cout << "See you soon!" << endl;
}
