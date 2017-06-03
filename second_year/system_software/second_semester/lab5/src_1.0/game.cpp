#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <process.h>
#include <sstream>
using namespace std;

#define MAX_SEM_COUNT 2

HANDLE getChampionshipStartEvent(int access){
  HANDLE hEvent;
  if (access == 1){
    hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, "championshipStartEvent");
  } else {
    hEvent = OpenEvent(SYNCHRONIZE, FALSE, "championshipStartEvent");
  }
  if (hEvent == NULL){
    cout << "creating event" << endl;
    hEvent = CreateEvent(NULL, TRUE, FALSE, "championshipStartEvent");
  }
  return hEvent;
}

HANDLE getFileMutex(){
  HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, "fileMutex");
  if (hMutex == NULL){
    hMutex = CreateMutex(NULL, FALSE, "fileMutex");
  }
  return hMutex;
}

HANDLE getGameSemaphore(){
  HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "fileMutex");
  if (hSemaphore == NULL){
    hSemaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, "getGameSemaphore");
  }
  return hSemaphore;
}

int writeUser(HANDLE fileMutex, const char* fileName, string login, string password){
  DWORD dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
  ofstream fout(fileName, ios_base::app);
  fout <<"$"<<login<<"/"<<password;
  fout.close();
  ReleaseMutex(fileMutex);
  return 0;
}

string covertStepToString(int num){
  if (num == 0){
    return "stone";
  }
  if (num == 1){
    return "scissors";
  }
  return "paper";
}

int covertStringToStep(string step){
  if (step.compare("stone") == 0){
    return 0;
  }
  if (step.compare("scissors") == 0){
    return 1;
  }
  if (step.compare("paper") == 0){
    return 2;
  }
  return -1;
}

int passToGame(int championship){
    HANDLE hSemaphore = getGameSemaphore();
    HANDLE hEvent;
    cout << "Waiting for queue..." << endl;
    DWORD dwWaitResult = WaitForSingleObject(hSemaphore, INFINITE);
    cout << "Welcome to the game!" << endl;
    if (championship == 1){
      hEvent = getChampionshipStartEvent(0);
      cout << "Waiting for starting championship..." << endl;
      WaitForSingleObject(hEvent, INFINITE);
    }
    int computer = 0;
    int user = 0;
    int num = 0;
    int computerNum = 0;
    string command;
    string comuputerCommand;
    int count = 0;
    int countComp = 0;
    srand(time(NULL));
    while (true){
        if ((championship == 1) && (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0)){
          cout << "Championship ended." << endl;
          CloseHandle(hEvent);
          break;
        }
        cout << "Let's go : \n - stone \n - scissors \n - paper \n - exit" << endl;
        getline(cin, command);
        if (command.compare("exit") == 0){
          cout << "Thank you for game!" << endl;
          cout << "End count "<<count<<" : "<<countComp<<endl;
          if (count > countComp){
            cout << "I win" << endl;
          } else if (count < countComp){
            cout << "You win" << endl;
          } else {
            cout << "Dead hit" << endl;
          }
          break;
        }
        num = covertStringToStep(command);
        cout << num;
        if (num == -1) continue;
        computerNum = rand() % 3;
        comuputerCommand = covertStepToString(computerNum);
        cout << "You've selected " << command << " and I've selected " << comuputerCommand << endl;
        if (((num == 0) && (computerNum == 1)) || ((num == 1) && (computerNum == 2)) || ((num == 2) && (computerNum == 0))){
          count++;
          cout << "You win. Count "<<count<<" : "<<countComp<<endl;
          continue;
        } else if (((num == 0) && (computerNum == 2)) || ((num == 1) && (computerNum == 0)) || ((num == 2) && (computerNum == 1))){
          countComp++;
          cout << "I win. Count "<<count<<" : "<<countComp<<endl;
          continue;
        } else {
          cout << "Dead hit. Count "<<count<<" : "<<countComp<<endl;
          continue;
        }

    }
    ReleaseSemaphore(hSemaphore, 1, NULL);
    CloseHandle(hSemaphore);
    return 0;
}

int checkUser(HANDLE fileMutex, const char* fileName, string login, string password){
  string rLogin;
  string rPassword;
  DWORD dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
  char buff[50];
  ifstream fin(fileName);
  int stop = 2;
  int del = 1;
  int index = 0;
  char ch;
  while ((stop!=0) && fin.get(ch)) {
    //cout << ch << endl;
    if (ch == '$'){
      stop--;
      if (stop == 0){
        stop = 1;
        del = 1;
        //cout << "login : " << rLogin << endl;
        //cout << "password : " << rPassword << endl;
        //cout << "-" << rLogin << "-" << rPassword << "-" << endl;
        if ((login.compare(rLogin) == 0) && (password.compare(rPassword) == 0)) return 0;
        //cout << "login is " << login.compare(rLogin) << "password is " << password.compare(rPassword) << endl;
        rLogin.clear();
        rPassword.clear();
      }
      continue;
    }
    if (ch == '/'){
      del--;
      continue;
    }
    if ((stop == 1) && (del == 1)){
      rLogin.append(1, ch);
      continue;
    }
    if ((stop == 1) && (del == 0) && (ch != '\n')){
      rPassword.append(1, ch);
      continue;
    }
  }
  //cout << "login : " << rLogin << endl;
  //cout << "password : " << rPassword << endl;
  //cout << "-" << rLogin << "-" << rPassword << "-" << endl;
  //cout << "login is " << login.compare(rLogin) << "password is " << password.compare(rPassword) << endl;
  if ((login.compare(rLogin) == 0) && (password.compare(rPassword) == 0)) return 0;
  fin.close();
  return 1;
}

string getData(const char* message, const char* forbiddenSymbols, int maxLength){
  string data;
  do{
    cout << message << endl;
    getline(cin, data);
  } while ((data.find_first_of(forbiddenSymbols) != string::npos) || (data.length() > maxLength));
  return data;
}

int registerUser(){
  HANDLE fileMutex = getFileMutex();
  string login = getData("Please, enter your login (less than or equals to 32 symbols without $ and /) and press Enter : ", "$/", 32);
  string password = getData("Please, enter your password (less than or equals to 32 symbols without $ and /) and press Enter : ", "$/", 32);
  writeUser(fileMutex,"users.txt",login,password);
  CloseHandle(fileMutex);
  return 0;
}

int admitUser(int championship){
  HANDLE fileMutex = getFileMutex();
  string login = getData("Please, enter your login and press Enter : ", "$/", 32);
  string password = getData("Please, enter your password and press Enter : ", "$/", 32);
  if (checkUser(fileMutex,"users.txt",login,password) == 0){
    ReleaseMutex(fileMutex);
    CloseHandle(fileMutex);
    passToGame(championship);
  } else {
    ReleaseMutex(fileMutex);
    CloseHandle(fileMutex);
    cout << "Invalid login or password" << endl;
  }
  return 0;
}

int startChamp(){
  string keyword;
  HANDLE hEvent = getChampionshipStartEvent(1);
  if (WaitForSingleObject(hEvent,0) == WAIT_OBJECT_0){
    cout << "Championship already started" << endl;
    return 0;
  }
  do{
    cout << "Please, type keyword for starting championship : " << endl;
    getline(cin, keyword);
  } while (keyword.compare("hexademical") != 0);
  if (WaitForSingleObject(hEvent,0) == WAIT_OBJECT_0){
    cout << "Championship already started" << endl;
    return 0;
  }
  cout << "before" << endl;
  //ResetEvent(hEvent);
  SetEvent(hEvent);
  cout << "after" << endl;
  if (WaitForSingleObject(hEvent,0) == WAIT_OBJECT_0){
    cout << "Championship have started !" << endl;
    return 0;
  }
  CloseHandle(hEvent);
  return 0;
}

int stopChamp(){
  string keyword;
  HANDLE hEvent = getChampionshipStartEvent(1);
  if (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0){
    cout << "Championship already stopped" << endl;
    return 0;
  }
  do{
    cout << "Please, type keyword for stopping championship : " << endl;
    getline(cin, keyword);
  } while (keyword.compare("hexademical") != 0);
  if (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0){
    cout << "Championship already stopped" << endl;
    return 0;
  }
  cout << "before" << endl;
  //SetEvent(hEvent);
  ResetEvent(hEvent);
  cout << "after" << endl;
  if (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0){
    cout << "Championship have stopped !" << endl;
    return 0;
  }
  CloseHandle(hEvent);
  return 0;
}

int main(int argc, char* argv[]){
  //passToGame();
  cout << "Welcome to the game!" << endl;
  string command = "";
  while(true){
    cout << "Menu : \n - login \n - signin \n - about \n - signinchampionship \n - startchampionship \n - stopchampionship \n - exit" << endl;
    getline(cin, command);
    if (command.compare("signin") == 0){
      admitUser(0);
    } else if (command.compare("signinchampionship") == 0){
      admitUser(1);
    } else if (command.compare("startchampionship") == 0){
      startChamp();
    } else if (command.compare("stopchampionship") == 0){
      stopChamp();
    } else if (command.compare("login") == 0){
      registerUser();
    } else if (command.compare("about") == 0){
      cout << "It's a sample of using multithreading in C++ via WinAPI." << endl;
      continue;
    } else if (command.compare("exit") == 0){
      cout << "Good buy!";
      return 0;
    }
  }
}
