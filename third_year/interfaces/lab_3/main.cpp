#include <Windows.h>
#include <stdio.h>

#define UNICODE
#define _UNICODE

using namespace std;

#define COPY	100	//Loads image
#define PASTE 2

class WndFrm
{
public:
    WndFrm();
    ~WndFrm(void);
    void CreateForm();
private:
    void GethInstence();
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
TCHAR CLASS_NAME[] = "WndClass";

WndFrm::WndFrm()
{
}

WndFrm::~WndFrm(void)
{
}

void WndFrm::CreateForm()
{
    HINSTANCE hInstence = (HINSTANCE) GetModuleHandle(NULL);

    WNDCLASS wc;

    wc.cbClsExtra = 0;                              //Дополнительные параметры класса
    wc.cbWndExtra = 0;                              //Дополнительные параметры окна
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);    //Цвет окна
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);       //Курсор
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);         //Иконка
    wc.hInstance = hInstence;                       //Дискриптор приложения
    wc.lpfnWndProc = WndProc;                       //Имя ф-ии обработки сообщений
    wc.lpszClassName = CLASS_NAME;                  //Имя класса окна
    wc.lpszMenuName = NULL;                         //Ссылка на главное меню
    wc.style = CS_VREDRAW | CS_HREDRAW;             //Стиль окна

    if(!RegisterClass(&wc))
    {
        MessageBox(NULL, "", "", MB_ICONERROR | MB_OK);
    }

    HWND hwnd = CreateWindow(CLASS_NAME, "Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstence, NULL);

		HMENU MainMenu = CreateMenu();
		AppendMenu(MainMenu, MF_STRING, COPY, TEXT("Copy"));
		AppendMenu(MainMenu, MF_STRING, PASTE, TEXT("Paste"));
		SetMenu(hwnd, MainMenu);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "", "", MB_OK);
    }
    ShowWindow(hwnd, SW_SHOW);

    MSG msg;

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void toClipboard(char* output){
		const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	printf("ok");
		HWND hEdit;
		RECT rect;
		int width;
		int height;
		if(GetWindowRect(hwnd, &rect))
		{
  		width = rect.right - rect.left;
  		height = rect.bottom - rect.top;
		}
		int editlength;
		char* lpstr = "OK";

		switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
      break;
		case WM_CREATE:
		MessageBox(hwnd, "CREATE", "edit text", 0);
		printf("ok");
			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",
			"Type Text Here\n",WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			0,0,width,height,hwnd,(HMENU)12,GetModuleHandle(NULL),
			NULL);
			break;
		case WM_COMMAND: {
				if (LOWORD(wParam) == COPY) {
					int length = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
					lpstr = (char*)malloc(length + 1);
					LPTSTR ok = (char*)malloc(length + 1);
					//SendMessage(hEdit, WM_GETTEXT, WPARAM(length+1), LPARAM(lpstr));
					if (GetWindowText(hEdit, ok, length+1)){
						MessageBox(hwnd, lpstr, "edit text", 0);
					} else {
						MessageBox(hwnd, "Failed", "edit text", 0);
					}

					toClipboard(lpstr);

				}}
				break;
		case WM_SIZE:
			MessageBox(hwnd, lpstr, "edit text", 0);
			printf("ok");
			if(GetWindowRect(hwnd, &rect))
			{
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;
			}
			DestroyWindow(hEdit);
			//hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",
			//"Type Text Here\n",WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			//0,0,width,height,hwnd,(HMENU)12,GetModuleHandle(NULL),
			//NULL);
			InvalidateRect(hwnd, NULL, NULL);
    default:
				printf("ok");
				return DefWindowProc(hwnd,uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstence, HINSTANCE, LPSTR pCmdLine, int nCmdLine)
{
    WndFrm from1;
    from1.CreateForm();
}
