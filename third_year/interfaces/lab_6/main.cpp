#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Commdlg.h>
#include <assert.h>
#include <tchar.h>
#include <string>
#include <time.h>  
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "headers\\basic_window.h"
#include "headers\\resource.h"
#include "headers\\mp3.h"
#include "headers\\flashlight_button.h"
#include "headers\\basic_button.h"
#include "headers\\main_window.h"

namespace fs = std::experimental::filesystem;

HBITMAP hLoadImage;
HBITMAP hLoadMask;

HBITMAP hExitImage;
HBITMAP hExitMask;

HBITMAP hBackgroundImage;
HBITMAP hBackgroundMask;

HBITMAP hFlashlightMask;

HBITMAP hPlayMask;
HBITMAP hPlayImage;

HBITMAP hPauseMask;
HBITMAP hPauseImage;

HBITMAP hPrevMask;
HBITMAP hPrevImage;

HBITMAP hNextMask;
HBITMAP hNextImage;

HBITMAP hSawImage;

MainWindow			* mainWindow;
BasicButton		* playButton;
BasicButton		* pauseButton;
BasicButton		* nextButton;
BasicButton		* prevButton;
BasicButton		* loadButton;
BasicButton		* exitButton;
FlashlightButton	* flashlightButton;

Mp3		mp3 = Mp3();
bool	playing;
bool	paused;
WCHAR	filename[MAX_PATH];
std::string fname;
std::string filenames[200];
int		filenames_size = 0;
int		current_filename = 0;
WIN32_FIND_DATA ffd;

int red = 0;
int channel = 2;
bool increasing = true;

/* Moving between tracks */

void ReLoad();

LPCWSTR s2ws(const std::string& s);

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

std::string GetShortPath(std::string fullPath) {
	std::string::size_type pos = fullPath.find_last_of("\\/");
	std::string filenameWithExtension = fullPath.substr(pos + 1, fullPath.length());
	pos = filenameWithExtension.find_last_of(".");
	return filenameWithExtension.substr(0, pos);
}

std::wstring GetShortPath(std::wstring fullPath) {
	std::string::size_type pos = fullPath.find_last_of(L"\\/");
	std::wstring filenameWithExtension = fullPath.substr(pos + 1, fullPath.length());
	pos = filenameWithExtension.find_last_of(L".");
	return filenameWithExtension.substr(0, pos);
}

void MoveToNext() {
	current_filename++;
	if (current_filename >= filenames_size) {
		current_filename = 0;
	}
	fname = filenames[current_filename];
	ReLoad();
}

void MoveToPrev() {
	current_filename--;
	if (current_filename < 0) {
		current_filename = filenames_size - 1;
	}
	fname = filenames[current_filename];
	ReLoad();
}

void UpdateTitle() {
	WCHAR filename_short[MAX_PATH];
	memcpy(filename_short, s2ws(GetShortPath(fname)), MAX_PATH);
	SetWindowText(mainWindow->m_hWnd, filename_short);
}

void UpdateTitle(std::wstring path) {
	WCHAR filename_short[MAX_PATH];
	memcpy(filename_short, GetShortPath(path).c_str(), MAX_PATH);
	SetWindowText(mainWindow->m_hWnd, filename_short);
}

void ReLoad() {
	mp3.Stop();
	memcpy(filename, s2ws(fname), MAX_PATH);
	mp3.Load(filename);
	mp3.Play();
	UpdateTitle();
	paused = false;
	playing = true;
}

std::string* GetFileNames()
{
	std::string path_o;
	std::string path = ExePath();
	bool isItMusic = false;
	int index = 0;
	for (auto & p : fs::directory_iterator(path+"\\music")) {
		isItMusic = false;
		path_o = p.path().string().substr(p.path().string().length() - 4);
		isItMusic = path_o == ".mp3";
		if (isItMusic){
			filenames[index] = p.path().string();
			index++;
		}
		std::cout << p << std::endl;
	}
	filenames_size = index;
	current_filename = 0;
	fname = filenames[0];
	return filenames;
}

std::string* GetFileNames(std::string file_path)
{
	std::string path_o;
	std::string::size_type pos = file_path.find_last_of("\\/");
	std::string path  = file_path.substr(0, pos);
	//std::string path = ExePath();
	bool isItMusic = false;
	int index = 0;
	for (auto & p : fs::directory_iterator(path)) {
		isItMusic = false;
		path_o = p.path().string().substr(p.path().string().length() - 4);
		isItMusic = path_o == ".mp3";
		if (isItMusic) {
			filenames[index] = p.path().string();
			if (filenames[index] == file_path) {
				current_filename = index;
				fname = filenames[index];
			}
			index++;
		}
		std::cout << p << std::endl;
	}
	filenames_size = index;
	//current_filename = 0;
	//fname = filenames[0];
	return filenames;
}

LPCWSTR s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	return buf;
}

std::string narrow(const std::wstring& wide, const std::locale& loc)
{
	if (wide.empty())
		return std::string();

	typedef std::wstring::traits_type::state_type state_type;
	typedef std::codecvt<wchar_t, char, state_type> CVT;

	const CVT& cvt = std::use_facet<CVT>(loc);
	std::string narrow(cvt.max_length()*wide.size(), '\0');
	state_type state = state_type();

	const wchar_t* from_beg = &wide[0];
	const wchar_t* from_end = from_beg + wide.size();
	const wchar_t* from_nxt;
	char* to_beg = &narrow[0];
	char* to_end = to_beg + narrow.size();
	char* to_nxt;

	std::string::size_type sz = 0;
	std::codecvt_base::result r;
	do
	{
		r = cvt.out(state, from_beg, from_end, from_nxt,
			to_beg, to_end, to_nxt);
		switch (r)
		{
		case std::codecvt_base::error:
			throw std::runtime_error("error converting wstring to string");

		case std::codecvt_base::partial:
			sz += to_nxt - to_beg;
			narrow.resize(2 * narrow.size());
			to_beg = &narrow[sz];
			to_end = &narrow[0] + narrow.size();
			break;

		case std::codecvt_base::noconv:
			narrow.resize(sz + (from_end - from_beg) * sizeof(wchar_t));
			std::memcpy(&narrow[sz], from_beg, (from_end - from_beg) * sizeof(wchar_t));
			r = std::codecvt_base::ok;
			break;

		case std::codecvt_base::ok:
			sz += to_nxt - to_beg;
			narrow.resize(sz);
			break;
		}
	} while (r != std::codecvt_base::ok);

	return narrow;
}

std::string ws2s(const std::wstring wstr)
{
	std::locale loc_russian("Russian");
	return narrow(wstr, loc_russian);
}

/* Button listeners */

void OpenClick(){
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = _T("MP3 files\0*.mp3\0\0");
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = _T("Please, select music file");
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)){
		UpdateTitle(std::wstring(filename));
		
		mp3.Load(filename);
		mp3.Play();
		GetFileNames(ws2s(std::wstring(filename)));
		paused = false;
		playing = true;
	}
}

void CloseClick(){
	mp3.Cleanup();
	PostMessage(mainWindow->m_hWnd, WM_CLOSE, 0, 0);
}

void PauseClick(){
	if ((playing) && (!paused)){
		paused = true;
		mp3.Pause();
	}
}

void PlayClick() {
	if (!playing) {
		if (mp3.Load(s2ws(fname)) && mp3.Play()) {
			paused = false;
			playing = true;
		}
	}
	else if (paused) {
		paused = false;
		mp3.Play();
	}
}

void ProgressBarClick()
{
	if (channel == 1) {
		channel = 2;
		return;
	}
		
	if (channel == 2) {
		channel = 3;
		return;
	}
		
	if (channel == 3) {
		channel = 1;
		return;
	}
		
}

/* Timers */

VOID CALLBACK ChangeBackgroundTimer(_In_ HWND     hwnd, _In_ UINT     uMsg, _In_ UINT_PTR idEvent, _In_ DWORD    dwTime){
	static bool blackSet = true;
	if (playing && !paused)
	{
		if (increasing)
			red += 10;
		else
			red -= 10;

		if (red > 255) {
			increasing = false;
			red = 254;
		}
		if (red < 0) {
			increasing = true;
			red = 0;
		}
			
		auto r = 0;
		auto g = 0;
		auto b = 0;

		if (channel == 1)
			r = red;
		if (channel == 2)
			g = red;
		if (channel == 3)
			b = red;

		flashlightButton->SetColor(RGB(r, g, b));
		blackSet = false;
	}
	else if (!blackSet)
	{
		flashlightButton->SetColor(RGB(0, 0, 0));
		blackSet = true;
	}
}

/* Main */

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmd, int nShow){
	/* Load filenames */
	GetFileNames();
	/* Load images */
	hLoadImage = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(LOAD_IMAGE_PATH), IMAGE_BITMAP, NULL, NULL, 0);
	hLoadMask = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(LOAD_MASK_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);

	hExitImage = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(EXIT_IMAGE_PATH), IMAGE_BITMAP, NULL, NULL, 0);
	hExitMask = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(EXIT_MASK_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);
	
	hBackgroundImage = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(BACKGROUND_IMAGE_PATH), IMAGE_BITMAP, NULL, NULL, 0);
	hBackgroundMask = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(BACKGROUND_MASK_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);
	
	hFlashlightMask = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(FLASHLIGHT_MASK_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);
	
	hPlayMask = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(PLAY_MASK_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);
	hPlayImage = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(PLAY_IMAGE_PATH), IMAGE_BITMAP, NULL, NULL, 0);
	
	hPauseMask = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(PAUSE_MASK_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);
	hPauseImage = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(PAUSE_IMAGE_PATH), IMAGE_BITMAP, NULL, NULL, 0);

	hPrevMask = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(PREV_MASK_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);
	hPrevImage = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(PREV_IMAGE_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);

	hNextMask = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(PAUSE_IMAGE_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);
	hNextImage = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(NEXT_IMAGE_PATH), IMAGE_BITMAP, NULL, NULL, LR_CREATEDIBSECTION | LR_MONOCHROME);

	/* Create buttons */
	
	mainWindow = new MainWindow(hInst, WS_POPUP, NULL, hBackgroundImage, hBackgroundMask, 0, 0);
	loadButton = new BasicButton(hInst, mainWindow->m_hWnd, hLoadImage, hLoadMask, 149, 158, OpenClick);
	exitButton = new BasicButton(hInst, mainWindow->m_hWnd, hExitImage, hExitMask, 244, 146, CloseClick);
	playButton = new BasicButton(hInst, mainWindow->m_hWnd, hPlayImage, hPlayMask, 281, 314, PlayClick);
	pauseButton = new BasicButton(hInst, mainWindow->m_hWnd, hPauseImage, hPauseMask, 413, 283, PauseClick);
	nextButton = new BasicButton(hInst, mainWindow->m_hWnd, hNextImage, hPauseMask, 349, 299, MoveToNext);
	prevButton = new BasicButton(hInst, mainWindow->m_hWnd, hPrevImage, hPauseMask, 314, 306, MoveToPrev);
	flashlightButton = new FlashlightButton(hInst, mainWindow->m_hWnd, RGB(0, 0, 255), RGB(0, 0, 127), hFlashlightMask, 1000, 206, 330, ProgressBarClick);

	flashlightButton->SetColor(RGB(0, 0, 0));
	
	/* Show windows */
	loadButton->ShowWindow(nShow);
	exitButton->ShowWindow(nShow);
	flashlightButton->ShowWindow(nShow);
	playButton->ShowWindow(nShow);
	pauseButton->ShowWindow(nShow);
	nextButton->ShowWindow(nShow);
	prevButton->ShowWindow(nShow);
	mainWindow->ShowWindow(nShow);

	/* Update windows */
	loadButton->UpdateWindow();
	exitButton->UpdateWindow();
	flashlightButton->UpdateWindow();
	playButton->UpdateWindow();
	pauseButton->UpdateWindow();
	nextButton->UpdateWindow();
	prevButton->UpdateWindow();
	mainWindow->UpdateWindow();

	/* Set timer */
	mainWindow->SetTimer(1, 70, ChangeBackgroundTimer);
	auto ret = mainWindow->MessageLoop();
	mainWindow->KillTimer(1);

	//return ret;
	return 0;
}

