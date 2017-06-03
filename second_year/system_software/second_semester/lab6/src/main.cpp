#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <thread>
#include "stdafx.h"

#pragma comment( lib, "user32.lib")
#pragma comment( lib, "gdi32.lib")

using namespace std;

HHOOK _hook;
KBDLLHOOKSTRUCT _eventInfo;

void showErrorMessage(){
  cout << "Usage : main hook|hotkey" << endl;
}

void showHookSetupFailed(){
  cout << "Hook setting failed" << endl;
}

void showHookSetupSuccessful(){
  cout << "Hook setting done" << endl;
}

void showHookReleaseFailed(){
  cout << "Hook releasing failed" << endl;
}

void showHookReleaseSuccessful(){
  cout << "Hook releasing done" << endl;
}


void showHotkeySetupFailed(){
  cout << "Hotkey setting failed" << endl;
}

void showHotkeySetupSuccessful(){
  cout << "Hotkey setting done" << endl;
}

void showHotkeyReleaseFailed(){
  cout << "Hotkey releasing failed" << endl;
}

void showHotkeyReleaseSuccessful(){
  cout << "Hotkey releasing done" << endl;
}

void releaseHook(){
  if (UnhookWindowsHookEx(_hook)){
      showHookReleaseSuccessful();
  } else {
    showHookReleaseFailed();
  }
}

LRESULT __stdcall hookCallback(int hookHandlingCode, WPARAM actionIdentifier, LPARAM eventInfo){
  if (hookHandlingCode >= 0){
    _eventInfo = *((KBDLLHOOKSTRUCT*)eventInfo);
    if (((actionIdentifier == WM_KEYDOWN) || (actionIdentifier == WM_SYSKEYDOWN)) && (GetAsyncKeyState(164) != 0)){
      if (_eventInfo.vkCode == 164){
        Beep(1000,500);
      } else if (_eventInfo.vkCode == 160){
        releaseHook();
      }
    }
  }
  return CallNextHookEx(_hook,hookHandlingCode,actionIdentifier,eventInfo);
}

void setHook(){
  if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL,hookCallback,NULL,0))){
      showHookSetupFailed();
  } else {
      showHookSetupSuccessful();
  }
}

void registerHotKey(){
  if (RegisterHotKey(NULL,1,MOD_ALT | MOD_NOREPEAT,0)){
    showHotkeySetupSuccessful();
  } else {
    showHotkeySetupFailed();
  }
}

int main(int argc, char* argv[]){
  char* hook = "hook";
  char* hotkey = "hotkey";

  setlocale(LC_ALL,"Russian");
  if (argc != 2){
    showErrorMessage();
    return 1;
  } else if (strcmp(argv[1],hook) == 0){
    cout << "Hook selected" << endl;
    setHook();
  } else if (strcmp(argv[1],hotkey) == 0){
    cout << "Hotkey selected" << endl;
    registerHotKey();
  } else {
    showErrorMessage();
    return 1;
  }

  MSG msg;
  while(GetMessage(&msg, NULL, 0, 0)){
    if (msg.message == WM_HOTKEY){
      Beep(1000,500);
    }
  }
  return 0;
}
