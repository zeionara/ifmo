#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <windows.h>
using namespace std;

int main(){
  HINSTANCE hDll = LoadLibrary("library.dll");
  VOID (*testfunctionprotype)(LPCTSTR);
  VOID (*sort)(LPDWORD);
  VOID (*strmask)();
  VOID (*fpu)(LPCTSTR, LPCTSTR, LPCTSTR, LPCTSTR, LPVOID);
  if (hDll == NULL){
    cout << "Library is not loaded"<< endl;
    return 1;
  }
  cout << "Library loaded" <<endl;
  FARPROC testfunction = GetProcAddress(hDll,"TestFunction");
  if (testfunction == NULL){
    cout << "Proc wasn't found" << endl;
    return 1;
  }
  cout << "Proc found" << endl;
  testfunctionprotype = (VOID(*)(LPCTSTR))testfunction;
  //testfunctionprotype("Soon");

  FARPROC firstlab = GetProcAddress(hDll,"FirstLab");
  if (firstlab == NULL){
    cout << "Proc wasn't found" << endl;
    return 1;
  }
  cout << "Proc found" << endl;
  sort = (VOID(*)(LPDWORD))firstlab;
  DWORD aac = 10;
  sort(&aac);
  cout << "Max element in original array from lab 1 is equal to " << *((LPDWORD)aac) << endl;

  FARPROC seclab = GetProcAddress(hDll,"SecLab");
  if (seclab == NULL){
    cout << "Proc wasn't found" << endl;
    return 1;
  }
  cout << "Proc found" << endl;
  strmask = (VOID(*)())seclab;
  strmask();
  string x0str = "1.1";
  string xnstr = "2.5";
  string step = "0.2";
  string acc = "0.0001";

  cout << "Please, type x0 : " << endl;
  //cin >> x0str;
  cout << "Please, type xn : " << endl;
  //cin >> xnstr;
  cout << "Please, type step : " << endl;
  //cin >> step;
  cout << "Please, type accuracy : " << endl;
  //cin >> acc;

  FARPROC sevlab = GetProcAddress(hDll,"SevLab");
  if (sevlab == NULL){
    cout << "Proc wasn't found" << endl;
    return 1;
  }
  cout << "Proc found" << endl;
  fpu = (VOID(*)(LPCTSTR, LPCTSTR, LPCTSTR, LPCTSTR, LPVOID))sevlab;
   cout << "kk" << endl;
  //cout << &&rre << endl;
  fpu("1.1", "2.5", "0.2", "0.0001", &&rre);

  cout << "oooo" << endl;
  rre: FreeLibrary(hDll);
}
