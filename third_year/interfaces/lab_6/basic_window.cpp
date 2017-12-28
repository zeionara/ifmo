#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h> 
#include <assert.h>
#include <tchar.h>
#include "headers\\basic_window.h"
#include "headers\\resource.h"

LRESULT BasicWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		OnKeyDown(wParam, lParam);
		return 0;
	case WM_KEYUP:
		OnKeyUp(wParam, lParam);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		BeginPaint(m_hWnd, &ps);
		OnDraw(ps);
		EndPaint(m_hWnd, &ps);
	}
	return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSELEAVE:
		OnMouseLeave(wParam, lParam);
		return 0;
	case WM_SETCURSOR:
		if (!OnSetCursor(wParam, lParam))
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_LBUTTONDOWN:
		OnMouseDown(wParam, lParam);
		return 0;
	case WM_LBUTTONUP:
		OnMouseUp(wParam, lParam);
		return 0;
	case WM_NCHITTEST:
		LRESULT ret = DoChitTest(hWnd, uMsg, wParam, lParam);
		if (ret == -1)
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		return ret;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK BasicWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BasicWindow * pWindow;

	if (uMsg == WM_NCCREATE)
	{
		assert(!IsBadReadPtr((void *)lParam, sizeof(CREATESTRUCT)));
		MDICREATESTRUCT * pMDIC = (MDICREATESTRUCT *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		pWindow = (BasicWindow *)(pMDIC->lParam);

		assert(!IsBadReadPtr(pWindow, sizeof(BasicWindow)));
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);
	}
	else
	{
		pWindow = (BasicWindow *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (pWindow)
		return pWindow->WndProc(hWnd, uMsg, wParam, lParam);
	else
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool BasicWindow::RegisterClass(LPCTSTR lpszClass, HINSTANCE hInst)
{
	WNDCLASSEX wc;

	

	if (!GetClassInfoEx(hInst, lpszClass, &wc))
	{
		GetWndClassEx(wc);

		
		wc.hInstance = hInst;
		//wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(BACKGROUND_IMAGE_PATH), IMAGE_BITMAP, 48, 48, LR_DEFAULTCOLOR));
		wc.lpszClassName = lpszClass;
		
		if (!RegisterClassEx(&wc))
			return false;
	}

	return true;
}

bool BasicWindow::CreateEx(DWORD dwExStyle, LPCTSTR lpszClass, LPCTSTR lpszName,
	DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hParent,
	HMENU hMenu, HINSTANCE hInst)
{
	if (!RegisterClass(lpszClass, hInst))
		return false;

	MDICREATESTRUCT mdic;
	memset(&mdic, 0, sizeof(mdic));
	mdic.lParam = (LPARAM) this;
	m_hWnd = CreateWindowEx(dwExStyle, lpszClass, lpszName, dwStyle,
		x, y, nWidth, nHeight, hParent, hMenu, hInst, &mdic);

	return m_hWnd != NULL;
}

void BasicWindow::GetWndClassEx(WNDCLASSEX & wc)
{
	memset(&wc, 0, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NULL;
	wc.hIconSm = NULL;
}

WPARAM BasicWindow::MessageLoop(void)
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

HRGN SumRegions(HRGN hRgn, int x1, int y1, int x2, int y2)
{
	if (hRgn == 0)
		hRgn = CreateRectRgn(x1, y1, x2, y2);
	else
		CombineRgn(hRgn, hRgn, CreateRectRgn(x1, y1, x2, y2), RGN_OR);
	return hRgn;
}

HRGN GetRegionFromMask(HBITMAP hBmp, HBITMAP * hMaskBmp)
{
	DIBSECTION section;
	BITMAP bm;
	GetObject(hBmp, sizeof(section), &section);
	bm = section.dsBm;

	BYTE * pMaskBits = (BYTE *)bm.bmBits;

	int maskWidth = (bm.bmWidth % 16 == 0 ? bm.bmWidth / 16 : bm.bmWidth / 16 + 1) * 2;
	auto pMask = new unsigned char[bm.bmHeight * maskWidth];
	auto pPlayBits = new unsigned char[bm.bmHeight * maskWidth];
	auto pExitBits = new unsigned char[bm.bmHeight * maskWidth];
	memset(pMask, 0, sizeof(unsigned char) * bm.bmHeight * maskWidth);
	memset(pPlayBits, 0, sizeof(unsigned char) * bm.bmHeight * maskWidth);
	memset(pExitBits, 0, sizeof(unsigned char) * bm.bmHeight * maskWidth);

	int pixel;
	int xStart = -1;
	HRGN hRgn = 0;
	for (int i = 0; i < bm.bmHeight; ++i)
	{
		for (int j = 0; j < bm.bmWidth; ++j)
		{
			pixel = (pMaskBits[i * bm.bmWidthBytes + j]);
			if (pixel != 0)
			{
				int mbyte = (bm.bmHeight - i - 1) * maskWidth + j / 8;
				unsigned char mask = 1 << (8 - (j % 8) - 1);
				pMask[mbyte] |= mask;
				if (xStart == -1)
				{
					xStart = j;
				}
			}

			if (xStart != -1 && (pixel == 0 || j == bm.bmWidth - 1))
			{
				hRgn = SumRegions(hRgn, xStart, bm.bmHeight - i - 1, j, bm.bmHeight - i);
				xStart = -1;
			}
		}
	}
	*hMaskBmp = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, pMask);

	delete(pMask);
	delete(pPlayBits);
	delete(pExitBits);

	return hRgn;
}