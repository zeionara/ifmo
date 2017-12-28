// ThirdLab.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ThirdLab.h"
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//Mine
HWND hEdit;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_THIRDLAB, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THIRDLAB));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THIRDLAB));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_THIRDLAB);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

TCHAR* GetClipboardText(HWND hWnd)
{
	if (!OpenClipboard(nullptr)) {
		MessageBox(hWnd, L"Failed", L"edit text", 0);
	}

	HANDLE hData = GetClipboardData(CF_UNICODETEXT);
	if (hData == nullptr) {
			MessageBox(hWnd, L"Failed", L"edit text", 0);
	}

	TCHAR* pszText = (TCHAR*)(GlobalLock(hData));
	if (pszText == nullptr) {
		MessageBox(hWnd, L"Failed", L"edit text", 0);
	}

	//std::string text(pszText);

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	return pszText;
}

void toClipboard(TCHAR* chValue, int length_, HWND hWnd) {
	if (OpenClipboard(NULL))
	{
		// 
		// EmptyClipboard sets the clipboard owner to NULL		        // 
		if (!EmptyClipboard()) goto OnError1;
		
		//TCHAR chValue[] = output;
		size_t nLength = _tcslen(chValue);
		size_t nByteOfBuffer = (nLength + 1) * sizeof(TCHAR);
		HGLOBAL hGlobal = NULL;
		hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, nByteOfBuffer);
		if (NULL == hGlobal) goto OnError1;
		LPTSTR pBuf = (LPTSTR)GlobalLock(hGlobal);
		if (NULL == pBuf)
		{
			GlobalFree(hGlobal);
			hGlobal = NULL;
		}

		_tcscpy_s(pBuf, nLength + 1, chValue);
#ifdef _UNICODE
		SetClipboardData(CF_UNICODETEXT, hGlobal);
#else
		SetClipboardData(CF_TEXT, hGlobal);
#endif
		GlobalUnlock(hGlobal);
	OnError1:
		MessageBox(hWnd, L"HelloClip", L"edit text", 0);

		CloseClipboard();
	}
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	LPTSTR lpstr = L"OK";
	int width;
	int height;
	if (GetWindowRect(hWnd, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

    switch (message)
    {
	case WM_CREATE: {
			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT",
			L"Type Text Here\n", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			0, 0, width, height, hWnd, (HMENU)12, GetModuleHandle(NULL),
			NULL);
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDM_ABOUT: {
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				int length = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
				lpstr = (LPTSTR)malloc(length + 1);
				char* ok = (char*)malloc(length + 1);
				TCHAR* buff = (TCHAR*)malloc(length+1);
				//SendMessage(hEdit, WM_GETTEXT, WPARAM(length+1), LPARAM(lpstr));
				if (GetWindowText(hEdit, buff, length + 1)) {
					//MessageBox(hWnd, buff, L"edit text", 0);
					toClipboard(buff, length, hWnd);
				}
				else {
					MessageBox(hWnd, L"Failed", L"edit text", 0);
					
				}}
                break;
			case IDM_EXIT: {
				//DestroyWindow(hWnd);
				//std::string str = ;
				//MessageBox(hWnd, (TCHAR*)str.c_str(), L"edit text", 0);
				SetWindowText(hEdit, GetClipboardText(hWnd));
			}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_SIZE:
		//MessageBox(hWnd, L"lp", L"edit text", 0);
		//printf("ok");
		if (GetWindowRect(hWnd, &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}
		DestroyWindow(hEdit);
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,L"EDIT",
		L"Type Text Here\n",WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
		0,0,width,height,hWnd,(HMENU)12,GetModuleHandle(NULL),
		NULL);
		InvalidateRect(hWnd, NULL, NULL);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
