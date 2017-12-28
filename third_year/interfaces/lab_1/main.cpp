//Local includes
//#include "stdafx.h"
//#include "Win32Project1.h"

//Global includes
#include <windows.h>
#include <time.h>
#include <sys/utime.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>

#define MAX_LOADSTRING 100

//Menu options
#define OPEN	1	//Loads image
#define APPLY_BITBLT	2 //Modifies colors by bit blt
#define APPLY_SETPIXEL	3 //Modifies colors by set pixel
#define START_TESTS	4	//Measures time and writes it to file

using namespace std;
using namespace std::chrono;

LPCTSTR getFileName();
int saveBitmap(HDC hdc, HBITMAP bm, int width, int height);
LRESULT CALLBACK handleWindowEvents(HWND, UINT, WPARAM, LPARAM);
void setPixelDisplay(HWND hwnd, HBITMAP hBitmap);
void setBlt(HWND hWnd, HBITMAP hBitmap);
void runTests(HWND hwnd);

bool isLoaded = false;
HBITMAP hBitmap;

//Main procedure
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	freopen("results\\file.txt", "w", stdout);
	HWND hWnd;
	WNDCLASS WndClass;
	MSG Msg;
	char szClassName[] = "Lab1";
  char imageStr[] = "Image";

	//Creating window class
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = handleWindowEvents;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = "Menu";
	WndClass.lpszClassName = szClassName;

	// Registering window class
	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}

	// Creating window
	hWnd = CreateWindow(szClassName, imageStr,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	//Creating menu
	HMENU MainMenu = CreateMenu();
	AppendMenu(MainMenu, MF_STRING, OPEN, TEXT("Open blt file"));
	AppendMenu(MainMenu, MF_STRING, APPLY_BITBLT, TEXT("Change color by BitBlt"));
	AppendMenu(MainMenu, MF_STRING, START_TESTS, TEXT("Run tests"));
	AppendMenu(MainMenu, MF_STRING, APPLY_SETPIXEL, TEXT("Change color by SetPixel"));
	SetMenu(hWnd, MainMenu);

	if (!hWnd) {
		MessageBox(NULL, "Cannot create window", "Error", MB_OK);
		return 0;
	}

	// Show window, start handling his messages
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

LRESULT CALLBACK handleWindowEvents(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT: {
		BITMAP bm;
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hwnd, &ps);

		HDC hCompatibleDC = CreateCompatibleDC(hDC);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);
		GetObject(hBitmap, sizeof(bm), &bm);
		BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
		SelectObject(hCompatibleDC, hOldBitmap);
		DeleteDC(hCompatibleDC);

		EndPaint(hwnd, &ps);
		break;
	}
	case WM_COMMAND: {
		if (LOWORD(wParam) == OPEN) {
			LPCTSTR fileName = getFileName();
			hBitmap = (HBITMAP)LoadImage(0, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			InvalidateRect(hwnd, NULL, TRUE);
			isLoaded = true;
		}
		if (LOWORD(wParam) == START_TESTS) {
			runTests(hwnd);
			break;
		}
		if (LOWORD(wParam) == APPLY_BITBLT) {
			if (!isLoaded) {
				break;
			}
			setBlt(hwnd, hBitmap);
		}
		if (LOWORD(wParam) == APPLY_SETPIXEL) {
			if (!isLoaded) {
				break;
			}
			setPixelDisplay(hwnd, hBitmap);
		}
		break;
	}
	default: {
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
	}
	return 0;
}

void runTests(HWND hwnd) {
	long int ms;
	HBITMAP cpy;
	high_resolution_clock::time_point start_time;
	duration<double> stats[20];
	for (int type = 0; type<2; type++) {
		printf(type ? "pixel:  " : "bitblt: ");
		for (int i = 1; i <= 10; i++) {
			cpy = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, i * 200, i * 200, 0);
			start_time = high_resolution_clock::now();
			switch (type) {
			case 0:
				setBlt(hwnd, cpy);
				break;
			case 1:
				setPixelDisplay(hwnd, cpy);
				break;
			}
			stats[type * 10 + (i - 1)] = high_resolution_clock::now() - start_time;


			cout << stats[type * 10 + (i - 1)].count();
			cout << "\t";

			DeleteObject(cpy);
		}
		printf("\n");
	}
}

void setBlt(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bm;
	HDC hCompatibleDC = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

	GetObject(hBitmap, sizeof(bm), &bm);

	SelectObject(hCompatibleDC, GetStockObject(DC_BRUSH));

  SetDCBrushColor(hCompatibleDC, RGB(255, 255, 0));
  BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, MERGECOPY);  //dest_color = src_color * 0x00FFFF
	BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, DSTINVERT); // dest_color = not(src_color * 0x00FFFF)
	SetDCBrushColor(hCompatibleDC, RGB(255, 255, 127));
	BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, MERGECOPY); //dest_color = not(src_color * 0x00FFFF) * 0x800000
	BitBlt(hCompatibleDC, 0, 0, bm.bmWidth, bm.bmHeight, hCompatibleDC, 0, 0, DSTINVERT); //dest_color = (src_color * 0x00FFFF) + 0x800000

	saveBitmap(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);

	InvalidateRect(hwnd, NULL, TRUE);

	SelectObject(hCompatibleDC, hOldBitmap);
	DeleteDC(hCompatibleDC);
}

void setPixelDisplay(HWND hwnd, HBITMAP hBitmap) {
	BITMAP bm;
	GetObject(hBitmap, sizeof(bm), &bm);

	HDC hCompatibleDC = CreateCompatibleDC(NULL);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hBitmap);

	for (int i = 0; i < bm.bmWidth/10; i++) {
		for (int j = 0; j < bm.bmHeight/10; j++) {
			SetPixel(hCompatibleDC, i, j, (GetPixel(hCompatibleDC, i, j) & 0x00FFFF) | 0x800000);
		}
	}

	SelectObject(hCompatibleDC, hOldBitmap);
	saveBitmap(hCompatibleDC, hBitmap, bm.bmWidth, bm.bmHeight);
	InvalidateRect(hwnd, NULL, TRUE);
	DeleteDC(hCompatibleDC);
	DeleteObject(hOldBitmap);
}

LPCTSTR getFileName() {
	return "images\\image.bmp";
}

int saveBitmap(HDC hdc, HBITMAP H, int width, int height) {
	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = height;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((width * bi.biBitCount + 31) / 32) * 4 * height;

	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char *lpbitmap = (char *)GlobalLock(hDIB);

	GetDIBits(hdc, H, 0,
		(UINT)height,
		lpbitmap,
		(BITMAPINFO *)&bi, DIB_RGB_COLORS);

	HANDLE hFile = CreateFile("images\\image_new.bmp",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
	bmfHeader.bfSize = dwSizeofDIB;
	bmfHeader.bfType = 0x4D42;

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	//Unlock and Free the DIB from the heap
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	//Close the handle for the file that was created
	CloseHandle(hFile);

	return 0;
}
