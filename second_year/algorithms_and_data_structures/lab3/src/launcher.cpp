#include <windows.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
  setlocale(LC_ALL,"Russian");
  HANDLE processHandle;
  DWORD processId;
  STARTUPINFO startUpInfo;
  SECURITY_ATTRIBUTES StdOutSA ={sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
  HANDLE hFileLog = CreateFile("log.out.txt",GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &StdOutSA, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  PROCESS_INFORMATION processInformation;
  const char* commandLine = "main_singletone";
  GetStartupInfo(&startUpInfo);
  startUpInfo.dwFlags = STARTF_USESTDHANDLES;
  startUpInfo.hStdOutput = hFileLog;
  //CreateProcess(NULL, (LPSTR)commandLineMorning, NULL, NULL, TRUE, 0, NULL, NULL, &startUpInfo, &processInformation);
  processHandle = processInformation.hProcess;
  processId = processInformation.dwProcessId;

  unsigned numberOfVertexes = 10001;
  unsigned numberOfEdges = 100000;
  unsigned step = 100000;
  unsigned minWeight = 1;
  unsigned maxWeight = 1000000;

  string numberOfVertexesS = to_string(numberOfVertexes);
  string numberOfEdgesS = to_string(numberOfEdges);
  string minWeightS = to_string(minWeight);
  string maxWeightS = to_string(maxWeight);
  string commandLineStr = "main_singletone " + numberOfVertexesS + " " + numberOfEdgesS + " " + minWeightS + " " + maxWeightS;
  const char* str;

  while (numberOfEdges <= 10000000){
    numberOfVertexesS = to_string(numberOfVertexes);
    numberOfEdgesS = to_string(numberOfEdges);
    minWeightS = to_string(minWeight);
    maxWeightS = to_string(maxWeight);
    commandLineStr = "main_singletone " + numberOfVertexesS + " " + numberOfEdgesS + " " + minWeightS + " " + maxWeightS;
    str = commandLineStr.c_str();
    cout << str << endl;
    CreateProcess(NULL, (LPSTR)str, NULL, NULL, TRUE, 0, NULL, NULL, &startUpInfo, &processInformation);
    processHandle = processInformation.hProcess;
    cout << "counting" << endl;
    WaitForSingleObject(processHandle,INFINITE);
    cout << "end counting" << endl;
    numberOfEdges+=step;
  }

  //WaitForMultipleObjects(3,processHandles,TRUE,INFINITE);
  CloseHandle(hFileLog);
}
