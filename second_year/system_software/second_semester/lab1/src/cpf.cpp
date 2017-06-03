#include <windows.h>
#include <errno.h>
#include <iostream>
#define BUF_SIZE 256

using namespace std;

int copyByCopyFile(const char* src, const char* dest){
  if (!CopyFile(src, dest, FALSE)){
    return 1;
  }
  return 0;
}

int main(int argc, char* argv[]){
  if (argc != 3){
    cout << "Usage : cpf src dest" << endl;
    return 1;
  }

  int result = copyByCopyFile(argv[1],argv[2]);

  switch (result){
    case 0:
      cout << "Succesfully done!" << endl;
      return 0;
    case 1:
      cout << "Error when copying files" << endl;
      return 1;
  }
}
