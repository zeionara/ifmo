#pragma once
#include <windows.h>

#include "basic_window.h"

class BasicButton : public BasicWindow
{
public:
	void(*OnClick)(void);

	void SetImage(HBITMAP hImage)
	{
		this->hImage = hImage;
		InvalidateRect(this->m_hWnd, NULL, FALSE);
	}

	BasicButton(HINSTANCE hInst, HWND hParent, HBITMAP hImage, HBITMAP hMask, int x, int y, void(*OnClick)(void));
private:
	HBITMAP hImage = NULL;
	HBITMAP hMask = NULL;
	bool wasPressed = false;

	void OnMouseDown(WPARAM wParam, LPARAM lParam) override;
	void OnMouseUp(WPARAM wParam, LPARAM lParam) override;
	void OnDraw(PAINTSTRUCT ps) override;
	BOOL OnSetCursor(WPARAM wParam, LPARAM lParam) override;
	void OnMouseLeave(WPARAM wParam, LPARAM lParam) override;
};
