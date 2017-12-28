#include <windows.h>
#include <time.h>
#include <tchar.h>
#include "conio.h"
#include <atlstr.h>



HBITMAP hbmp = (HBITMAP)LoadImage(NULL, "mask.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION); // Todo: Hardcode your own path
BITMAP bm;
SIZE bmpSize = { 139, 139 }; // Todo: Hardcode your own bmp size
int step = 0;
POINT dcOffset = { 0, 0 };
POINT bmpOffset = { 100 , 0 };
int screenWidth = 0, screenHeight = 0;

HWND hWnd;
HDC hdc;
HHOOK keyPressHook;
BLENDFUNCTION blendFunc;

TCHAR CLASS_NAME[] = "WndClass";



void CALLBACK Do_Step(_In_ HWND hWnd, _In_ UINT uMsg, _In_ UINT_PTR idEvent, _In_ DWORD dwTime) {
	bmpOffset.y = bmpOffset.y + step;
	UpdateLayeredWindow(hWnd, NULL, &bmpOffset, &bmpSize, hdc, &dcOffset, 0, &blendFunc, ULW_ALPHA);

	if (bmpOffset.y > screenHeight) {
		bmpOffset.y = - bmpSize.cy;
	} else if (bmpOffset.y < - bmpSize.cy) {
		bmpOffset.y = screenHeight;
	}

	UpdateLayeredWindow(hWnd, 0, &bmpOffset, &bmpSize, hdc, &dcOffset, 0, &blendFunc, ULW_ALPHA);
}

void UpdateDesktopSize(int& horizontal, int& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
	bmpOffset.x = (int)(horizontal/2) - (int)(bmpSize.cx/2);
	UpdateLayeredWindow(hWnd, 0, &bmpOffset, &bmpSize, hdc, &dcOffset, 0, &blendFunc, ULW_ALPHA);
}

LRESULT __declspec(dllexport)__stdcall  CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
    if (wParam == WM_MOUSEWHEEL){
			MSLLHOOKSTRUCT *pMhs = (MSLLHOOKSTRUCT *)lParam;
			short zDelta = HIWORD(pMhs->mouseData);
			if (zDelta > 0){
				step ++;
			} else {
				step --;
			}
		}
  }

	return CallNextHookEx(keyPressHook, nCode, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	printf("ok");
		HWND hEdit;
		RECT rect;
		int width;
		int height;
		if(GetWindowRect(hwnd, &rect))
		{
  		width = rect.right - rect.left;
  		height = rect.bottom - rect.top;
		}
		int editlength;
		char* lpstr = "OK";

		switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
      break;
		case WM_CREATE:
		  //MessageBox(hwnd, "CREATE", "edit text", 0);
			break;
    default:
				printf("ok");
				return DefWindowProc(hwnd,uMsg, wParam, lParam);
    }

    return 0;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//HINSTANCE hInstence = (HINSTANCE) GetModuleHandle(NULL);
	//SetTimer(hWnd, 1, 10, (TIMERPROC)Do_Step);
	//WNDCLASS wc;

	//wc.cbClsExtra = 0;                              //Дополнительные параметры класса
	//wc.cbWndExtra = 0;                              //Дополнительные параметры окна
	//wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);    //Цвет окна
	//wc.hCursor = LoadCursor(NULL, IDC_ARROW);       //Курсор
	//wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);         //Иконка
	//wc.hInstance = hInstance;                       //Дискриптор приложения
  //wc.lpfnWndProc = WndProc;                       //Имя ф-ии обработки сообщений
	//wc.lpszClassName = CLASS_NAME;                  //Имя класса окна
	//wc.lpszMenuName = NULL;                         //Ссылка на главное меню
	//wc.style = CS_VREDRAW | CS_HREDRAW;             //Стиль окна

	char* CLASS_NAME  = "Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

	if(!RegisterClass(&wc))
	{
			MessageBox(NULL, "", "", MB_ICONERROR | MB_OK);
	}

	HWND hwnd = CreateWindow(CLASS_NAME, "Window", WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
			MessageBox(NULL, "", "", MB_OK);
	}

	//HRGN hRgn = CreateEllipticRgn(0, 0, 400, 400);
	//SetWindowRgn(hWnd, hRgn, TRUE);
	//ShowWindow(hwnd, nCmdShow);
	//UpdateWindow(hWnd);

	// --------------------------------------------------
// Создаём круглый регион.
// Используем отрицательную начальную координату, чтобы наш элипс
// захватил заголовок окна.
// --------------------------------------------------
HRGN hRegion1 = CreateEllipticRgn(20,-20,190,150);

// --------------------------------------------------
// создаём ещё один круглый регион в другом месте.
// --------------------------------------------------
HRGN hRegion2 = CreateEllipticRgn(140,100,300,240);

// --------------------------------------------------
// склеиваем два региона, чтобы сделать новый регион.
// итоговый регион будет помещён в region1,
// подобно операции:
//
//          hRegion1 = hRegion1 + hRegion2.
//
// в функции CombineRgn() можно использовать набор операций RGN_.
// --------------------------------------------------
CombineRgn(hRegion1, hRegion1, hRegion2, RGN_OR);

// --------------------------------------------------
// прикрепляем регион к окну
// --------------------------------------------------
//if (
SetWindowRgn(hWnd, hRegion1, true);
// == 0){
//	MessageBox(hWnd, "CREATE", "edit text", 0);
//};

// --------------------------------------------------
// удаляем объекты регионов
// --------------------------------------------------
DeleteObject(hRegion1);
DeleteObject(hRegion2);

ShowWindow(hwnd, nCmdShow);
UpdateWindow(hWnd);

	MSG msg;

	while(GetMessage(&msg, NULL, 0, 0))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}

	keyPressHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)KeyboardProc, 0, 0);
	/*
	//UpdateDesktopSize(screenWidth, screenHeight);
	TCHAR WinName[] = _T("Figure");
	WNDCLASSEX WndEx = { 0 };
	WndEx.cbSize = sizeof(WNDCLASSEX);
	WndEx.lpfnWndProc = DefWindowProc;
	WndEx.hInstance = hInstance;
	WndEx.lpszClassName = WinName;
	RegisterClassEx(&WndEx);
	//hWnd = CreateWindowEx(WS_EX_LAYERED, WinName, 0, WS_POPUP,
	//	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	HWND hWnd = CreateWindow("Figure", "OOP", WS_POPUP, 100, 100, 400, 400, NULL, NULL, hInstance, NULL);
	//SetTimer(hWnd, 1, 10, (TIMERPROC)Do_Step);

	//HDC hdcScreen = GetDC(0);
	//hdc = CreateCompatibleDC(hdcScreen);
	//ReleaseDC(0, hdcScreen);
	//(HBITMAP)SelectObject(hdc, hbmp);
	CString t;


	GetObject(hbmp, sizeof(bm), &bm);
	t.Format(_T("%d"), bm.bmWidth);
	MessageBox(hWnd, t , "ok", MB_OK);
	BYTE *pMaskBits = (BYTE *)bm.bmBits;

	int pixel;
	int xStart = -1;
	HRGN hRgn = 0;
	for (int i = 0; i < bm.bmHeight; i++) {
		for (int j = 0; j < bm.bmWidth; j++) {
				pixel = (pMaskBits[i * bm.bmWidthBytes + j]);
				if (pixel != 0){
					if (xStart == -1) xStart = j;
				} else if (xStart != -1) {
					if (hRgn == 0){
						hRgn = CreateRectRgn(xStart, bm.bmHeight - i - 1, j, bm.bmHeight - i);
					} else {
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

	SetWindowRgn(hWnd, hRgn, TRUE);

	//HRGN hRgn = CreateEllipticRgn(0, 0, 400, 400); SetWindowRgn(hWnd, hRgn, TRUE); ShowWindow(hWnd, nCmdShow); UpdateWindow(hWnd);


	//blendFunc.BlendOp = AC_SRC_OVER;
	//blendFunc.BlendFlags = 0;
	//blendFunc.SourceConstantAlpha = 255;
	//blendFunc.AlphaFormat = AC_SRC_ALPHA;
	//UpdateLayeredWindow(hWnd, 0, &bmpOffset, &bmpSize, hdc, &dcOffset, 0, &blendFunc, ULW_ALPHA);
	hRgn = CreateEllipticRgn(0, 0, 400, 400);
	SetWindowRgn(hWnd, hRgn, TRUE);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//keyPressHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)KeyboardProc, 0, 0);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;*/
}
