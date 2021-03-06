#include "stdafx.h"
#include "mainGame.h"
//API :: Application Programming Interface

//Àü¿ªº¯¼ö
HINSTANCE	_hInstance;		
HWND		_hWnd;			

LPCSTR _lpszClass = TEXT("Neptune Window API");

POINT _ptMouse;

mainGame _mg;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;		
	WNDCLASS	wndClass;		

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										
	wndClass.cbWndExtra = 0;										
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				
	wndClass.hInstance = hInstance;									
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						
	wndClass.lpszClassName = WINNAME;							    
	wndClass.lpszMenuName = NULL;									
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						

																	
	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,		
		WINSTARTX,					
		WINSTARTY,					
		WINSIZEX,					
		WINSIZEY,					
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	ShowWindow(_hWnd, cmdShow);

	if (FAILED(_mg.init()))
	{
		return 0;
	}

	/*
	while (GetMessage(&message, 0, 0, 0))
	{
	TranslateMessage(&message);	
	DispatchMessage(&message);	
	}
	*/
	while (true) {
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else {
			TIMEMANAGER->update(60.0f);
			_mg.update();
			_mg.render();
		}
	}

	_mg.release(); 

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}