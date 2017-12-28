//initialization
case WM_CREATE:

	//Get context of device
	hDC = GetDC(hWnd);
	//Get coordinates of the client area of the window
	GetClientRect(hWnd, &rect);

	dX = rect.right / 100.;
	dY = rect.bottom / 50.;

	//For changing ball's position
	SetTimer(hWnd, 1, 100, NULL);

	hBmpBkgr = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDB_STONE));

	hBkBrush = CreatePatternBrush(hBmpBkgr);

	//Replaces a handle to the background brush associated with the class associated with the window.
	SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)hBkBrush);
 
	hBmpBall = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDB_BALL));

	//Get bitmap
	GetObject(hBmpBall, sizeof(bm), (LPSTR)&bm);
	//For using world transformations
 	SetGraphicsMode(hDC, GM_ADVANCED);
	break;

//step of animation
case WM_TIMER:
	GetClientRect(hWnd, &rect);
	//Erase ball
	SetRect(&rBall, (int)x, (int)y, (int)x + bm.bmWidth, (int)y + bm.bmHeight);
	FillRect(hDC, &rBall, hBkBrush);
 
	//Change ball's position
	x += dX;
	y += dY;
	alpha += 10;
	if (alpha > 360)  alpha = 0;
 
	//Change direction for the next step if necessary
	if(x + bm.bmWidth > rect.right || x < 0) dX = -dX;
	if(y + bm.bmHeight > rect.bottom || y < 0) dY = -dY;

 	DrawBall(hWnd, hDC, hBmpBall, bm, x, y, alpha);
	break;

case WM_DESTROY:
	KillTimer(hWnd, 1);
	ReleaseDC(hWnd, hDC);
	PostQuitMessage(0);
	break;

...

void DrawBall(HWND hwnd, HDC hdc, HBITMAP hBmp, BITMAP bm, FLOAT x, FLOAT y, int alpha) {
	XFORM xform;
	HRGN hRgn;

	// Подготовка к выводу мяча
	HDC hBallMemDC = CreateCompatibleDC(hdc);
	SelectObject(hBallMemDC, hBmp);

	// Создаем регион отсечения
	hRgn = CreateEllipticRgn(x, y, x + bm.bmWidth, y + bm.bmHeight);
	SelectClipRgn(hdc, hRgn);

	// Мировые преобразования для перемещения и //вращения мяча
	xform.eM11 = (FLOAT) cos(alpha * 2 * Pi / 360);	 //вращение
	xform.eM12 = (FLOAT) sin(alpha * 2 * Pi / 360);	 //вращение
	xform.eM21 = (FLOAT) -sin(alpha * 2 * Pi / 360); //вращение
	xform.eM22 = (FLOAT) cos(alpha * 2 * Pi / 360);	 //вращение
	xform.eDx  = x + bm.bmWidth / 2.;		 //смещение по оси x
	xform.eDy  = y + bm.bmHeight / 2.;		 //смещение по оси y

	// Вывод мяча
	SaveDC(hdc);
	BOOL ret = SetWorldTransform(hdc, &xform);
	BitBlt(hdc, -bm.bmWidth/2, -bm.bmHeight/2, bm.bmWidth, bm.bmHeight, hBallMemDC, 0, 0, SRCCOPY);
	RestoreDC(hdc, -1);
 
	SelectClipRgn(hdc, NULL);
	DeleteObject(hRgn);
	DeleteDC(hBallMemDC);
