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

#define MAX_LENGTH 256;

#define MAX_SEM_COUNT 2

CRITICAL_SECTION criticalSection;

typedef struct _ThreadInfo
{
    char* fileName;
    char* identifier;
    int delay;
    HANDLE hSemaphore;
} ThreadInfo, *ThreadInfoPointer;

HANDLE getSemaphore(char* fileName){
  char semaphoreName[256] = "Semaphore";
  strcat(semaphoreName,fileName);
  HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, semaphoreName);
  if (hSemaphore == NULL){
    hSemaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, semaphoreName);
  }
  return hSemaphore;
}



unsigned __stdcall find(void* threadArg) {
  ThreadInfoPointer threadInfo = (ThreadInfoPointer)threadArg;
  HANDLE hSemaphore = threadInfo->hSemaphore;
  cout << "Waiting for semaphore..." << endl;
  WaitForSingleObject(hSemaphore, INFINITE);
  cout << "search started for identifier " << threadInfo->identifier << endl;



  char identifier[256];
  DWORD dwWaitResult;
  //HANDLE fileMutex = getFileMutex(argv[1]);

  //dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
  ifstream identifiers(threadInfo->fileName);


  if (!identifiers){
    cout << "error" << endl;
    return 1;
  }

  int index = 0;
  while (identifiers){
    identifiers.getline(identifier, 256);
    //cout << "-<" << threadInfo->identifier << ">-" << endl;
    //cout << "-<" << identifier << ">-" << endl;
    if (strcmp(identifier,threadInfo->identifier) == 0){
      cout << "identifier \'" << threadInfo->identifier << "\' " << "found at the position " << index << endl;
      ReleaseSemaphore(hSemaphore, 1, NULL);
      return 0;
    }
    index++;
    Sleep(threadInfo->delay);
    //cout << ".";
  }
  identifiers.close();
  cout << "Wasn't found" << endl;
  ReleaseSemaphore(hSemaphore, 1, NULL);
  return 1;
}

void main(int argc, char* argv[])
{
  DWORD dwWaitResult;
  HANDLE hSemaphore = getSemaphore(argv[1]);
  char identifier[256];
  string command = "";
  while(true){
    cout << "Type identifier to search in file (type exit to stop) : " << endl;
    getline(cin, command);
    if (command.compare("exit") == 0){
      break;
    }
    ThreadInfo* threadInfo = (ThreadInfo*)malloc(sizeof(ThreadInfo));
    threadInfo->fileName = argv[1];
    threadInfo->identifier = (char*)malloc(256*sizeof(char));
    strcpy(threadInfo->identifier, command.c_str());
    threadInfo->delay = 100;
    threadInfo->hSemaphore = hSemaphore;
    //cout << "Waiting for queue..." << endl;
    //dwWaitResult = WaitForSingleObject(hSemaphore, INFINITE);
    _beginthreadex(NULL, 0, find, threadInfo, 0, 0);
    //ReleaseSemaphore(hSemaphore, 1, NULL);
    //dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
    //ofstream ofs (argv[1], std::ofstream::app);
    //ofs<<command<<"\n";
    //ofs.close();

    //cout << "Releasing mutex" << endl;
    //ReleaseMutex(fileMutex);
    //cout << "Mutex released" << endl;
  }
}
