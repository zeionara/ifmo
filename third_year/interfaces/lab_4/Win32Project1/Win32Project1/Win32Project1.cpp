// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100


HBITMAP hbmp = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Zerbs\\Desktop\\interfaces\\lab_4\\star.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION); // Todo: Hardcode your own path
BITMAP bm;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

POINT bmpOffset = { 100 , 0 };
SIZE bmpSize = { 139, 139 }; // Todo: Hardcode your own bmp size
int step = 1;
int screenWidth = 0, screenHeight = 0;
HHOOK wheelRotatedHook;

LRESULT __declspec(dllexport)__stdcall  CALLBACK WheelProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		if (wParam == WM_MOUSEWHEEL) {
			MSLLHOOKSTRUCT *pMhs = (MSLLHOOKSTRUCT *)lParam;
			short zDelta = HIWORD(pMhs->mouseData);
			if (zDelta > 0) {
				step++;
			}
			else {
				step--;
			}
		}
	}

	return CallNextHookEx(wheelRotatedHook, nCode, wParam, lParam);
}

void UpdateWindowPosition(HWND hWnd) {
	SetWindowPos
	(
		hWnd,			// дескриптор окна
		HWND_TOP,		// дескриптор порядка размещения
		bmpOffset.x,				// позиция по горизонтали
		bmpOffset.y,				// позиция по вертикали
		bmpSize.cx,				// ширина
		bmpSize.cy,				// высота
		0 			// флажки позиционирования окна
	);
}


void UpdateDesktopSize(int& horizontal, int& vertical, HWND hWnd) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
	bmpOffset.x = (int)(horizontal / 2) - (int)(bmpSize.cx / 2);
	UpdateWindowPosition(hWnd);
}


void CALLBACK Do_Step(_In_ HWND hWnd, _In_ UINT uMsg, _In_ UINT_PTR idEvent, _In_ DWORD dwTime) {
	bmpOffset.y = bmpOffset.y + step;

	if (bmpOffset.y > screenHeight) {
		bmpOffset.y = -bmpSize.cy;
	}
	else if (bmpOffset.y < -bmpSize.cy) {
		bmpOffset.y = screenHeight;
	}
	UpdateWindowPosition(hWnd);
}

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
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, (WS_BORDER),
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   SetWindowLong(hWnd, GWL_STYLE, WS_BORDER);  // With 1 point border

   UpdateDesktopSize(screenWidth, screenHeight, hWnd);

   SetTimer(hWnd, 1, 10, (TIMERPROC)Do_Step);

   wheelRotatedHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)WheelProc, 0, 0);

   if (!hWnd)
   {
      return FALSE;
   }

   GetObject(hbmp, sizeof(bm), &bm);
   //t.Format(_T("%d"), bm.bmWidth);
   //MessageBox(hWnd, t, L"ok", MB_OK);
   BYTE *pMaskBits = (BYTE *)bm.bmBits;

   int pixel;
   int xStart = -1;
   HRGN hRgn = 0;
   for (int i = 0; i < bm.bmHeight; i++) {
	   for (int j = 0; j < bm.bmWidth; j++) {
		   pixel = (pMaskBits[i * bm.bmWidthBytes + j]);
		   if (pixel != 0) {
			   if (xStart == -1) xStart = j;
		   }
		   else if (xStart != -1) {
			   if (hRgn == 0) {
				   hRgn = CreateRectRgn(xStart, bm.bmHeight - i - 1, j, bm.bmHeight - i);
			   }
			   else {
				   CombineRgn(hRgn, hRgn, CreateRectRgn(xStart,
					   bm.bmHeight - i - 1, j, bm.bmHeight - i), RGN_OR);
				   xStart = -1;
			   }
		   }

		   if (j == bm.bmWidth - 1 && xStart != -1) {
			   if (hRgn == 0)
				   hRgn = CreateRectRgn(xStart, bm.bmHeight - i - 1, j + 1, bm.bmHeight - i);
			   else CombineRgn(hRgn, hRgn, CreateRectRgn(xStart, bm.bmHeight - i - 1, j + 1, bm.bmHeight - i), RGN_OR);
			   xStart = -1;
		   }
	   }
   }

   // --------------------------------------------------
   // прикрепляем регион к окну
   // --------------------------------------------------
   //if (
   SetWindowRgn(hWnd, hRgn, true);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    /*case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;*/
	case WM_PAINT:
	{
		PAINTSTRUCT     ps01;
		HDC             hdc01;
		BITMAP          bitmap01;
		HDC             hdcMem01;
		HGDIOBJ         oldBitmap01;

		hdc01 = BeginPaint(hWnd, &ps01);

		hdcMem01 = CreateCompatibleDC(hdc01);
		oldBitmap01 = SelectObject(hdcMem01, hbmp);

		GetObject(hbmp, sizeof(bitmap01), &bitmap01);
		BitBlt(hdc01, 0, 0, bitmap01.bmWidth, bitmap01.bmHeight, hdcMem01, 0, 0, SRCCOPY);

		SelectObject(hdcMem01, oldBitmap01);
		DeleteDC(hdcMem01);

		EndPaint(hWnd, &ps01);
	}
	break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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
