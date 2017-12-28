#include "headers\\basic_button.h"
#include <tchar.h>

BasicButton::BasicButton(HINSTANCE hInst, HWND hParent, HBITMAP hImage, HBITMAP hMask, int x, int y, void(*OnClick)(void))
{
	BITMAP bm;
	GetObject(hMask, sizeof(bm), &bm);

	this->hImage = hImage;

	this->OnClick = OnClick;
	this->BasicWindow::CreateEx(0, _T("play_button"), _T("play_button"), WS_CHILD, x, y, bm.bmWidth, bm.bmHeight, hParent, NULL, hInst);

	HRGN hRgn = GetRegionFromMask(hMask, &(this->hMask));

	SetWindowRgn(this->m_hWnd, hRgn, TRUE);
}

void BasicButton::OnMouseDown(WPARAM wParam, LPARAM lParam)
{
	wasPressed = true;
}

void BasicButton::OnMouseUp(WPARAM wParam, LPARAM lParam)
{
	if (wasPressed && OnClick != NULL)
		OnClick();
	wasPressed = false;
}

void BasicButton::OnDraw(PAINTSTRUCT ps)
{
	HDC hDC = ps.hdc;
	BITMAP image;
	GetObject(hImage, sizeof(BITMAP), &image);
	HDC hdcBuffer = CreateCompatibleDC(hDC);
	HBITMAP hBmpBuffer = CreateCompatibleBitmap(hDC, image.bmWidth, image.bmHeight);

	SelectObject(hdcBuffer, hBmpBuffer);

	HDC hdcComp = CreateCompatibleDC(hDC);
	SelectObject(hdcComp, hImage);
	MaskBlt(hdcBuffer, 0, 0, image.bmWidth, image.bmHeight, hdcComp, 0, 0, hMask, 0, 0, SRCCOPY);
	DeleteDC(hdcComp);

	BitBlt(hDC, 0, 0, image.bmWidth, image.bmHeight, hdcBuffer, 0, 0, SRCCOPY);

	DeleteDC(hdcBuffer);
	DeleteObject(hBmpBuffer);
}

BOOL BasicButton::OnSetCursor(WPARAM wParam, LPARAM lParam)
{
	SetCursor(LoadCursor(NULL, IDC_HAND));
	return TRUE;
}


void BasicButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	wasPressed = false;
}