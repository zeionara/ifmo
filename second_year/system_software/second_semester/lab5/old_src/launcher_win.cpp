#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
using namespace std;

int showTime(const char* overture, LPSYSTEMTIME systemTime){
  cout << overture << systemTime->wHour << ":" << systemTime->wMinute << ":" << systemTime->wSecond << ":" << systemTime->wMilliseconds;
  return 0;
}

int showDelemiter(int height, int width){
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      cout << "-";
    }
    cout << endl;
  }
  return 0;
}


int main(int argc, char* argv[]){
  setlocale(LC_ALL,"Russian");
  HANDLE* processHandles;
  DWORD* processIds;
  DWORD numOfOpenedHandles;
  processHandles = (HANDLE*)malloc(3*sizeof(HANDLE));
  processIds = (DWORD*)malloc(3*sizeof(DWORD));

  STARTUPINFO startUpInfo;
  FILETIME creationFileTime;
  SYSTEMTIME creationSystemTime;
  FILETIME exitFileTime;
  SYSTEMTIME exitSystemTime;
  FILETIME userFileTime;
  SYSTEMTIME userSystemTime;
  FILETIME kernelFileTime;
  SYSTEMTIME kernelSystemTime;
  
  SECURITY_ATTRIBUTES StdOutSA ={sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
	
  HANDLE hFileLog = CreateFile("log.out",GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &StdOutSA, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  
  
  PROCESS_INFORMATION processInformationMorning;
  PROCESS_INFORMATION processInformationEvening;
  PROCESS_INFORMATION processInformationDay;
  const char* commandLineMorning = "main data/lullaby.txt asc data/lullaby.txt.srtd утро";
  const char* commandLineDay = "main data/ghosts.txt desc data/ghosts.txt.srtd день";
  const char* commandLineEvening = "main data/widow.txt asc data/widow.txt.srtd вечер";
  GetStartupInfo(&startUpInfo);
  startUpInfo.dwFlags = STARTF_USESTDHANDLES;
  startUpInfo.hStdOutput = hFileLog;

  CreateProcess(NULL, (LPSTR)commandLineMorning, NULL, NULL, TRUE, 0, NULL, NULL, &startUpInfo, &processInformationMorning);
  CreateProcess(NULL, (LPSTR)commandLineDay, NULL, NULL, TRUE, 0, NULL, NULL, &startUpInfo, &processInformationDay);
  CreateProcess(NULL, (LPSTR)commandLineEvening, NULL, NULL, TRUE, 0, NULL, NULL, &startUpInfo, &processInformationEvening);

  processHandles[0] = processInformationMorning.hProcess;
  processHandles[1] = processInformationDay.hProcess;
  processHandles[2] = processInformationEvening.hProcess;

  processIds[0] = processInformationMorning.dwProcessId;
  processIds[1] = processInformationDay.dwProcessId;
  processIds[2] = processInformationEvening.dwProcessId;

  WaitForMultipleObjects(3,processHandles,TRUE,INFINITE);
  for (int i = 0; i < 3; i++){
    cout << "Process " << processIds[i];
    GetProcessTimes(processHandles[i],&creationFileTime,&exitFileTime,&kernelFileTime,&userFileTime);
    FileTimeToSystemTime(&creationFileTime,&creationSystemTime);
    FileTimeToSystemTime(&exitFileTime,&exitSystemTime);
    FileTimeToSystemTime(&userFileTime,&userSystemTime);
    FileTimeToSystemTime(&kernelFileTime,&kernelSystemTime);
    cout << showTime(" was created at ",&creationSystemTime);
    cout << showTime(", was exited at ",&exitSystemTime);
    cout << showTime(", so it was handling by kernel in ",&kernelSystemTime);
    cout << showTime(", and by user in ",&userSystemTime) << endl;
	GetProcessHandleCount(processHandles[i],&numOfOpenedHandles);
	cout << "In the process " << numOfOpenedHandles << " descriptors were opened" << endl;
  }
  CloseHandle(hFileLog);
}
