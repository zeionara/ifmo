// ZagDll.cpp: определяет процедуры инициализации для DLL.
//

#include "stdafx.h"
#include "ZagDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC. Это означает, что
//		он должен быть первым оператором 
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CZagDllApp

BEGIN_MESSAGE_MAP(CZagDllApp, CWinApp)
END_MESSAGE_MAP()


// создание CZagDllApp

CZagDllApp::CZagDllApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CZagDllApp

CZagDllApp theApp;


// инициализация CZagDllApp

BOOL CZagDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
