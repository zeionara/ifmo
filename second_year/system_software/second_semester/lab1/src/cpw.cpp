#include <windows.h>
#include <errno.h>
#include <iostream>
#define BUF_SIZE 256

using namespace std;

int copyByWin(const char* src, const char* dest){
  HANDLE hIn, hOut;
  DWORD nIn, nOut;
  CHAR Buffer[BUF_SIZE];
  hIn = CreateFile(src, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hIn == INVALID_HANDLE_VALUE){
    return 1;
  }
  hOut = CreateFile(dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hOut == INVALID_HANDLE_VALUE){
    return 1;
  }
  while(ReadFile(hIn,Buffer,BUF_SIZE,&nIn,NULL)&&nIn>0){
    WriteFile(hOut, Buffer, nIn, &nOut, NULL);

    if (nIn != nOut){

      return 2;
    }
  }
  CloseHandle(hIn);
  CloseHandle(hOut);
  return 0;
}

int main(int argc, char* argv[]){
  if (argc != 3){
    cout << "Usage : cpw src dest" << endl;
    return 1;
  }

  int result = copyByWin(argv[1],argv[2]);

  switch (result){
    case 0:
      cout << "Succesfully done!" << endl;
      return 0;
    case 1:
      cout << "Error when opening files" << endl;
      return 1;
    case 2:
      cout << "Internal error when copying" << endl;
      return 1;
  }
}
