#include <fstream>
#include <windows.h>
#include <iostream>
#include <process.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>
#include <array>
#include <stdio.h>
using namespace std;

HANDLE getFileMutex(char* fileName){
  char fileMutexName[256] = "fileMutex";
  strcat(fileMutexName,fileName);
  cout << "get mut" << endl;
  HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, fileMutexName);
  cout << "got mut" << endl;
  if (hMutex == NULL){
    hMutex = CreateMutex(NULL, FALSE, fileMutexName);
  }
  return hMutex;
}

void main(int argc, char* argv[])
{
  HANDLE fileMutex = getFileMutex(argv[1]);
  DWORD dwWaitResult;

  string command = "";
  while(true){
    cout << "Type identifier to write to file (type exit to stop) : " << endl;
    getline(cin, command);
    if (command.compare("exit") == 0){
      break;
    }
    dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
    ofstream ofs (argv[1], std::ofstream::app);
    ofs<<command<<"\n";
    ofs.close();
    cout << "Releasing mutex" << endl;
    ReleaseMutex(fileMutex);
    cout << "Mutex released" << endl;
  }

}
