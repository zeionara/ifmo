#include <tchar.h>
#include <Windowsx.h>

#include "headers\\flashlight_button.h"

void FlashlightButton::SetColor(COLORREF backgroundColor)
{
	if (background)
		DeleteObject(background);
	this->background = CreateSolidBrush(backgroundColor);
	InvalidateRect(this->m_hWnd, NULL, FALSE);
}

FlashlightButton::FlashlightButton(HINSTANCE hInst, HWND hParent, COLORREF foreground, 
	COLORREF background, HBITMAP hMask, long long maxStep, int x, int y, void(*OnUserClick)())
{
	BITMAP bm;
	GetObject(hMask, sizeof(bm), &bm);

	this->BasicWindow::CreateEx(0, _T("flashlight_button"), _T("flashlight_button"), WS_CHILD, x, y, bm.bmWidth, bm.bmHeight, hParent, NULL, hInst);

	HRGN hRgn = GetRegionFromMask(hMask, &(this->hMask));

	SetWindowRgn(this->m_hWnd, hRgn, TRUE);

	this->width = bm.bmWidth;
	this->height = bm.bmHeight;
	this->background = CreateSolidBrush(background);
	this->OnUserClick = OnUserClick;
}

void FlashlightButton::OnMouseDown(WPARAM wParam, LPARAM lParam)
{
	wasPressed = true;
}

void FlashlightButton::OnMouseUp(WPARAM wParam, LPARAM lParam)
{
	if (wasPressed)
		OnClick(wParam, lParam);;
	wasPressed = false;
}

void FlashlightButton::OnClick(WPARAM wParam, LPARAM lParam)
{
	if (OnUserClick)
		OnUserClick();
}

void FlashlightButton::OnDraw(PAINTSTRUCT ps)
{

	HDC hDC = ps.hdc;
	HDC srcDC = CreateCompatibleDC(hDC);
	HDC destDC = CreateCompatibleDC(hDC);
	HBITMAP destBMP = CreateCompatibleBitmap(hDC, width, height);
	HBITMAP srcBMP = CreateCompatibleBitmap(hDC, width, height);

	SelectObject(srcDC, srcBMP);
	SelectObject(destDC, destBMP);

	BitBlt(srcDC, 0, 0, width, height, destDC, 0, 0, BLACKNESS);
	SelectObject(destDC, background);
	// paint the background
	BitBlt(destDC, 0, 0, width, height, srcDC, 0, 0, 0x00FC008A);

	// copy to paint dc
	MaskBlt(hDC, 0, 0, width, height, destDC, 0, 0, hMask, 0, 0, SRCCOPY);

	// clean-up
	DeleteObject(srcBMP);
	DeleteObject(srcBMP);
	DeleteDC(srcDC);
	DeleteDC(destDC);
}

BOOL FlashlightButton::OnSetCursor(WPARAM wParam, LPARAM lParam)
{
	SetCursor(LoadCursor(NULL, IDC_HAND));
	return TRUE;
}