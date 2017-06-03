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

CRITICAL_SECTION criticalSection;

typedef struct _ThreadInfo
{
    HANDLE hFinishEvent;
    char** a;
    char** b;
    int low;
    int high;
} ThreadInfo, *ThreadInfoPointer;

int showThreadInfo(ThreadInfo threadInfo){
  cout << "Thread :" << endl;
  cout << " low - " << threadInfo.low << endl;
  cout << " hight - " << threadInfo.high << endl;
  return 0;
}

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

unsigned __stdcall mergesort(void* threadArg) {

  ThreadInfoPointer threadInfo = (ThreadInfoPointer)threadArg;

  if ((threadInfo->low) < (threadInfo->high))
  {
    HANDLE hEvents[2];
    hEvents[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
    hEvents[1] = CreateEvent(NULL, TRUE, FALSE, NULL);
    EnterCriticalSection(&criticalSection);
    //showThreadInfo(*threadInfo);
    LeaveCriticalSection(&criticalSection);
    int ridge = ((threadInfo->low)+(threadInfo->high))/2;
    ThreadInfo firstSubThreadInfo;
    ThreadInfo secondSubThreadInfo;

    firstSubThreadInfo.a = threadInfo->a;
    firstSubThreadInfo.b = threadInfo->b;
    firstSubThreadInfo.low = threadInfo->low;
    firstSubThreadInfo.high = ridge;
    firstSubThreadInfo.hFinishEvent = hEvents[0];

    secondSubThreadInfo.a=threadInfo->a;
    secondSubThreadInfo.b=threadInfo->b;
    secondSubThreadInfo.low=ridge+1;
    secondSubThreadInfo.high=threadInfo->high;
    secondSubThreadInfo.hFinishEvent = hEvents[1];

    EnterCriticalSection(&criticalSection);
    //cout << "Creating thread with " << firstSubThreadInfo.low << " and " << firstSubThreadInfo.high << endl;
    LeaveCriticalSection(&criticalSection);
    _beginthreadex(NULL, 0, mergesort, &firstSubThreadInfo, 0, 0);

    _beginthreadex(NULL, 0, mergesort, &secondSubThreadInfo, 0, 0);

    WaitForMultipleObjects(2,hEvents,true,INFINITE);

    EnterCriticalSection(&criticalSection);
    //cout << "Subthreads finished" << endl;
    LeaveCriticalSection(&criticalSection);

    int h,i,j,k,lowBound, highBound;

    lowBound = threadInfo->low;
    highBound = threadInfo->high;
    h=lowBound;
    i=lowBound;
    j=ridge+1;

    while((h <= ridge) && (j <= highBound))
     {
         if(strcmp(threadInfo->a[h],threadInfo->a[j]) <= 0)
         {
             threadInfo->b[i] = threadInfo->a[h];
             h++;
         } else {
             threadInfo->b[i] = threadInfo->a[j];
             j++;
          }
          i++;
     }

    if(h > ridge)
    {
        for (k = j; k <= highBound; k++)
        {
            threadInfo->b[i]=threadInfo->a[k];
            i++;
        }
     } else {
        for ( k = h; k <= ridge; k++)
           {
               threadInfo->b[i]=threadInfo->a[k];
               i++;
           }
    }

    for(k = lowBound; k <= highBound; k++) threadInfo->a[k]=threadInfo->b[k];

  }

  if (threadInfo->hFinishEvent != INVALID_HANDLE_VALUE) SetEvent(threadInfo->hFinishEvent);
  return 0;
}

void main(int argc, char* argv[])
{
  char identifier[256];
  DWORD dwWaitResult;
  HANDLE fileMutex = getFileMutex(argv[1]);

  while (true){
  dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
  ifstream identifiers(argv[1]);

  if (!identifiers){
    return;
  }

  int numOfElements = 0;
  while (identifiers){
    identifiers.getline(identifier, 256);
    //cout << identifier << endl;
    numOfElements++;
  }

  identifiers.close();

  cout << numOfElements << endl;

  char** idents = (char**)malloc(numOfElements*sizeof(char*));
  char** identstmp = (char**)malloc(numOfElements*sizeof(char*));

  ifstream identifierss(argv[1]);



  if (!identifierss){
    return;
  }



  int index = 0;
  while (identifierss){
    idents[index] = (char*)malloc(256*sizeof(char*));
    identifierss.getline(idents[index], 256);
    //cout << idents[index] << endl;
    //cout << identifier << endl;
    index++;
  }

  identifierss.close();

  InitializeCriticalSection(&criticalSection);

  ThreadInfo threadInfo;
  int inputArr[12] = {12,10,43,23,-78,45,123,56,98,41,90,24};
  int copiedArr[12]={0,0,0,0,0,0,0,0,0,0,0,0};

  threadInfo.a=idents;
  threadInfo.b=identstmp;

  //for(int i=0; i<numOfElements; i++) cout<<threadInfo.a[i]<<" ";
  //cout<<endl;

  HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  threadInfo.low = 0;
  threadInfo.high = numOfElements - 1;
  threadInfo.hFinishEvent = hEvent;

  _beginthreadex(NULL, 0, mergesort, &threadInfo, 0, 0);

  WaitForSingleObject(hEvent, 5000);
  //cout << "oss" << endl;
  cout<<"After run the result is "<<endl;
  for(int i=0; i<numOfElements; i++) cout<<threadInfo.a[i]<<" ";
  cout<<endl;

  ofstream ofs (argv[1], std::ofstream::out);
  for(int i=0; i<numOfElements; i++) ofs<<threadInfo.a[i]<<"\n";
  ofs.close();
  cout << "Releasing mutex" << endl;
  ReleaseMutex(fileMutex);
  cout << "Mutex released" << endl;
}
}
