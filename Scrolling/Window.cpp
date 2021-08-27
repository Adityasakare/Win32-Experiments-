#include <windows.h>
#include <stdio.h>
#define LINES 26

LRESULT CALLBACK WndProc ( HWND,
						  UNIT,
						  WPARAM,
						  LPARAM);

int WINAPI WinMain ( HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTER lpszCmdLine,
					 int nCmdShow)

{

	//Local Varibales

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	char AppName[] = "Windows";

	// Code

	wndclass.cbSize = sizeof( WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Registration
	RegisterClassEx (&wndclass);

	// Creation of Window
	hwnd = CreateWindow(AppName,
						"Aditya's Window",
						 WS_OVERLAPPEDWINDOW,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 CW_USEDEFAULT,
						 NULL,
						 NULL,
						 hInstance,
						 NULL);

	//Displaying of Window

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	// Message loop

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);

	// End of WinMain()
} 

	// Window Procedure (Window Function) :

LRESULT CALLBACK WndProc (HWND hwnd,
						  UNIT iMsg,
						  WPARAM wParam,
						  LPARAM lParam)
{

	// Declaration of local varibles

	switch(iMsg)
	{
		
	}
}