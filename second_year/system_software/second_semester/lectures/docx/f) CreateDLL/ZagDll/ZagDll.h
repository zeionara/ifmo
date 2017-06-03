// ZagDll.h: главный файл заголовка для DLL ZagDll
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CZagDllApp
// Про реализацию данного класса см. ZagDll.cpp
//

class CZagDllApp : public CWinApp
{
public:
	CZagDllApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
