
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

CRITICAL_SECTION criticalSection;

typedef struct _ThreadInfo
{
    HANDLE hFinishEvent;
    int* a;
    int* b;
    int low;
    int high;
} ThreadInfo, *ThreadInfoPointer;

int showThreadInfo(ThreadInfo threadInfo){
  cout << "Thread :" << endl;
  cout << " low - " << threadInfo.low << endl;
  cout << " hight - " << threadInfo.high << endl;
  return 0;
}

unsigned __stdcall mergesort(void* threadArg) {

  ThreadInfoPointer threadInfo = (ThreadInfoPointer)threadArg;

  if ((threadInfo->low) < (threadInfo->high))
  {
    HANDLE hEvents[2];
    hEvents[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
    hEvents[1] = CreateEvent(NULL, TRUE, FALSE, NULL);
    EnterCriticalSection(&criticalSection);
    showThreadInfo(*threadInfo);
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
    cout << "Subthreads finished" << endl;
    LeaveCriticalSection(&criticalSection);

    int h,i,j,k,lowBound, highBound;

    lowBound = threadInfo->low;
    highBound = threadInfo->high;
    h=lowBound;
    i=lowBound;
    j=ridge+1;

    while((h <= ridge) && (j <= highBound))
     {
         if(threadInfo->a[h] <= threadInfo->a[j])
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

void main()
{


  InitializeCriticalSection(&criticalSection);

  ThreadInfo threadInfo;
  int inputArr[12] = {12,10,43,23,-78,45,123,56,98,41,90,24};
  int copiedArr[12]={0,0,0,0,0,0,0,0,0,0,0,0};

  threadInfo.a=inputArr;
  threadInfo.b=copiedArr;

  for(int i=0; i<12; i++) cout<<threadInfo.a[i]<<" ";
  cout<<endl;

  HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  threadInfo.low = 0;
  threadInfo.high = 11;
  threadInfo.hFinishEvent = hEvent;

  _beginthreadex(NULL, 0, mergesort, &threadInfo, 0, 0);

  WaitForSingleObject(hEvent, INFINITE);

  cout<<"After run the result is "<<endl;
  for(int i=0; i<12; i++) cout<<inputArr[i]<<" ";
  cout<<endl;
}
