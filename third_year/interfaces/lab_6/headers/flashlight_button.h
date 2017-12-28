#pragma once
#include <windows.h>

#include "basic_window.h"

class FlashlightButton : public BasicWindow
{
public:
	void(*OnUserClick)() = NULL;

	void SetColor(COLORREF backgroundColor);

	FlashlightButton(HINSTANCE hInst, HWND hParent, COLORREF foreground, COLORREF background, 
		HBITMAP hMask, long long maxStep, int x, int y, void(*OnUserClick)());
private:
	long long maxStep;
	long long currStep;
	HBITMAP hMask;
	HBRUSH background = NULL;
	bool wasPressed = false;
	int width;
	int height;

	~FlashlightButton()
	{
		if (background)
			DeleteObject(background);
	}

	void OnMouseDown(WPARAM wParam, LPARAM lParam) override;
	void OnMouseUp(WPARAM wParam, LPARAM lParam) override;
	void OnClick(WPARAM wParam, LPARAM lParam);
	BOOL OnSetCursor(WPARAM wParam, LPARAM lParam) override;
	void OnDraw(PAINTSTRUCT ps) override;
};
