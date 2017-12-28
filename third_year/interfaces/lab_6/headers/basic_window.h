//kwindow.h
#pragma once

#include <windows.h>

class BasicWindow
{
	virtual LRESULT DoChitTest(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return -1;
	}

	virtual void OnDraw(PAINTSTRUCT ps)
	{}

	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam)
	{}

	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam)
	{}

	virtual void OnMouseMove(WPARAM wParam, LPARAM lParam)
	{}

	virtual void OnMouseLeave(WPARAM wParam, LPARAM lParam)
	{}

	virtual BOOL OnSetCursor(WPARAM wParam, LPARAM lParam)
	{
		return FALSE;
	}

	virtual void OnMouseDown(WPARAM wParam, LPARAM lParam)
	{}
	
	virtual void OnMouseUp(WPARAM wParam, LPARAM lParam)
	{}

	virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual void GetWndClassEx(WNDCLASSEX & wc);
public:
	HWND m_hWnd;
	BasicWindow(void)
	{
		m_hWnd = NULL;
	}

	virtual ~BasicWindow(void)
	{}

	virtual bool CreateEx(DWORD dwExStyle, LPCTSTR lpszClass, LPCTSTR lpszName,
		DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hParent,
		HMENU hMenu, HINSTANCE hInst);

	bool RegisterClass(LPCTSTR lpszClass, HINSTANCE hInst);

	virtual WPARAM MessageLoop(void);

	BOOL ShowWindow(int nCmdShow) const
	{
		return ::ShowWindow(m_hWnd, nCmdShow);
	}

	BOOL RedrawWindow(void) const
	{
		::InvalidateRect(m_hWnd, NULL, TRUE);
		return ::UpdateWindow(m_hWnd);
	}

	BOOL UpdateWindow(void) const
	{
		return ::UpdateWindow(m_hWnd);
	}

	UINT_PTR SetTimer(UINT_PTR timerId, UINT uElapse, TIMERPROC lpTimerFunc)
	{
		return ::SetTimer(this->m_hWnd, timerId, uElapse, lpTimerFunc);
	}

	BOOL KillTimer(UINT_PTR timerId)
	{
		return ::KillTimer(this->m_hWnd, timerId);
	}

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

HRGN SumRegions(HRGN hRgn, int x1, int y1, int x2, int y2);

HRGN GetRegionFromMask(HBITMAP hBmp, HBITMAP * hMaskBmp);