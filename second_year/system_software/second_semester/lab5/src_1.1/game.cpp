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

CRITICAL_SECTION criticalSection;

HANDLE getChampionshipStartEvent(int access){
  HANDLE hEvent;
  if (access == 1){
    hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, "championshipStartEvent");
  } else {
    hEvent = OpenEvent(SYNCHRONIZE, FALSE, "championshipStartEvent");
  }
  if (hEvent == NULL){
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
  HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "gameSemaphore");
  if (hSemaphore == NULL){
    hSemaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, "gameSemaphore");
  }
  return hSemaphore;
}

int writeUser(HANDLE fileMutex, const char* fileName, string login, string password){
  DWORD dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
  ofstream fout(fileName, ios_base::app);
  fout <<"$"<<login<<"/"<<password;
  fout.close();
  Sleep(15000);
  ReleaseMutex(fileMutex);
  return 0;
}

string convertStepToString(int num){
  if (num == 0){
    return "stone";
  }
  if (num == 1){
    return "scissors";
  }
  return "paper";
}

int convertStringToStep(string step){
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
          break;
        }
        num = convertStringToStep(command);
        cout << num;
        if (num == -1) continue;
        computerNum = rand() % 3;
        comuputerCommand = convertStepToString(computerNum);
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
    cout << "Thank you for game!" << endl;
    cout << "End count "<<count<<" : "<<countComp<<endl;
    if (count > countComp){
      cout << "I win" << endl;
    } else if (count < countComp){
      cout << "You win" << endl;
    } else {
      cout << "Dead hit" << endl;
    }
    ReleaseSemaphore(hSemaphore, 1, NULL);
    CloseHandle(hSemaphore);
    return 0;
}

int checkUser(HANDLE fileMutex, const char* fileName, string login, string password){

  string rLogin;
  string rPassword;
  cout << "Waiting for acessing data file ... " << endl;
  DWORD dwWaitResult = WaitForSingleObject(fileMutex,INFINITE);
  cout << "Data file acessed " << endl;
  ifstream fin(fileName);
  int stop = 2;
  int del = 1;
  int index = 0;
  char ch;
  while ((stop!=0) && fin.get(ch)) {
    if (ch == '$'){
      stop--;
      if (stop == 0){
        stop = 1;
        del = 1;
        if ((login.compare(rLogin) == 0) && (password.compare(rPassword) == 0)) return 0;
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

int* generateDeck(int sizeOfDeck){
  srand(time(NULL));
  int* deck = (int*)malloc(sizeOfDeck*sizeof(int));
  for (int i = 0; i < sizeOfDeck; i++){
    deck[i] = rand() % 3;
  }
  return deck;
}

int shuffleDeck(int* deck, int sizeOfDeck){
  srand(time(NULL));
  int tmp = 0;
  for (int i = 0; i < rand() % sizeOfDeck; i++){
    for (int j = 0; j < rand() % sizeOfDeck; j++){
      tmp = deck[i];
      deck[i] = deck[j];
      deck[j] = tmp;
    }
  }
  return 0;
}

unsigned __stdcall reShuffleDeck(void* pThArg) {
  LPDWORD params = (LPDWORD)pThArg;
  int* sizePtr = (int*)params[0];
  int* deck = (int*)params[1];
  while(true){
    if (*sizePtr <= 0){
      _endthreadex(0);
    }
    EnterCriticalSection(&criticalSection);
    shuffleDeck(deck,*sizePtr);
    Sleep(5000);
    LeaveCriticalSection(&criticalSection);
    Sleep(1000);
  }
  return 0;
}

int passToCards(){
  srand(time(NULL));
  unsigned int threadId;
  cout << "Welcome to the stone, scissors and paper cards !" << endl;
  int* deck = generateDeck(10);
  int deckSize = 10;
  DWORD params[2];
  params[0] = (DWORD)&deckSize;
  params[1] = (DWORD)deck;
  HANDLE deckShuffler = (HANDLE)_beginthreadex(NULL, 0, reShuffleDeck, params, CREATE_SUSPENDED, &threadId);
  ResumeThread(deckShuffler);
  int n;
  int m;
  int num;
  int computerNum;
  int count = 0;
  int countComp = 0;
  int tmp;
  while (deckSize > 0){
    cout << "Select card : " << endl;
    do{
      scanf ("%d",&n);
    }while ((n < 0) || (n >= deckSize));
    do{
      m = rand() % deckSize;
    } while (m==n);
    cout << "I select " << m << endl;
    cout << "Waiting for shuffler ..." << endl;
    EnterCriticalSection(&criticalSection);
    num = deck[n];
    computerNum = deck[m];

    deck[n] = deck[deckSize-1];
    deck[deckSize-1] = num;
    deckSize--;

    deck[m] = deck[deckSize-1];
    deck[deckSize-1] = computerNum;
    deckSize--;

    LeaveCriticalSection(&criticalSection);
    cout << "So, I've got "<<convertStepToString(computerNum)<<" and you've got "<<convertStepToString(num)<<endl;
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
  cout << "Thank you for game!" << endl;
  cout << "End count "<<count<<" : "<<countComp<<endl;
  if (count > countComp){
    cout << "I win" << endl;
  } else if (count < countComp){
    cout << "You win" << endl;
  } else {
    cout << "Dead hit" << endl;
  }
  return 0;
}

int admitUser(int championship){
  HANDLE fileMutex = getFileMutex();
  string login = getData("Please, enter your login and press Enter : ", "$/", 32);
  string password = getData("Please, enter your password and press Enter : ", "$/", 32);
  if (checkUser(fileMutex,"users.txt",login,password) == 0){
    ReleaseMutex(fileMutex);
    CloseHandle(fileMutex);
    if (championship == 2){
      passToCards();
      return 0;
    }
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
  SetEvent(hEvent);
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
  ResetEvent(hEvent);
  if (WaitForSingleObject(hEvent,0) != WAIT_OBJECT_0){
    cout << "Championship have stopped !" << endl;
    return 0;
  }
  CloseHandle(hEvent);
  return 0;
}

int main(int argc, char* argv[]){
  InitializeCriticalSection(&criticalSection);
  bool continueType = true;
  bool continueSubType = true;
  cout << "Welcome to the game!" << endl;
  string command = "";
  while(true){
    cout << "Menu : \n - login \n - signin \n - startchamp \n - stopchamp \n - about \n - exit" << endl;
    continueType = true;
    while (continueType){
      getline(cin, command);
      if (command.compare("signin") == 0){
        cout << "Play mode : \n - plain \n - champ \n - cards \n - exit" << endl;
        continueSubType = true;
        while (continueSubType){
          getline(cin, command);
          if (command.compare("plain") == 0){
            admitUser(0);
            continueSubType = false;
          } else if (command.compare("champ") == 0){
            admitUser(1);
            continueSubType = false;
          } else if (command.compare("cards") == 0){
            admitUser(2);
            continueSubType = false;
          } else if (command.compare("exit") == 0){
            continueSubType = false;
          }
        }
        continueType = false;
      } else if (command.compare("startchamp") == 0){
        startChamp();
        continueType = false;
      } else if (command.compare("stopchamp") == 0){
        stopChamp();
        continueType = false;
      } else if (command.compare("login") == 0){
        registerUser();
        continueType = false;
      } else if (command.compare("about") == 0){
        cout << "---------System--Software-------\nIt's a sample of using multithreading in C++ via WinAPI." << endl;
        continueType = false;
      } else if (command.compare("exit") == 0){
        cout << "Good buy!";
        ExitProcess(0);
      }
    }
  }
}
