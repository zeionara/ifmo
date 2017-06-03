#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <ctime>
using namespace std;

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
  if (argc != 3){
    cout << "Usage : filegen path/to/file num_of_identifiers";
    return 1;
  }

  int result = generateFile(atoi(argv[2]),argv[1],3,32);

  if (result == 0){
    cout << "All perfect! File " << argv[1] << " with " << atoi(argv[2]) << " identifiers created." << endl;
    return 0;
  }
  cout << "There is error" << endl;
  return 1;

}
