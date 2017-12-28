#pragma once

#include <windows.h>
#include "basic_window.h"

class MainWindow : public BasicWindow
{
public:
	MainWindow(HINSTANCE hInst, DWORD dwStyle, HWND hParent, HBITMAP hImage, HBITMAP hMask, int x, int y);
private:
	HBITMAP hMainBackground;
	HBITMAP hMainMaskBMP;

	void OnDraw(PAINTSTRUCT ps) override;
	LRESULT DoChitTest(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};