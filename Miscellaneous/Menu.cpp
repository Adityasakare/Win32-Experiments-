#include <windows.h>

#define FILE_MENU_NEW 1 
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
// Global Function declerations

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

void AddMenu(HWND);

// Global Variable Declarations

HMENU hMenu;
// Entry point functions

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Variable Declarations

	WNDCLASSEX wndclass;
	HWND hwnd;
	//HWND hwndButton;
	MSG msg;
	TCHAR szAppName [] = TEXT("MyWindow");

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);

	




	RegisterClassEx(&wndclass);

	//Create window in memory
	hwnd = CreateWindow(szAppName,
						TEXT("BUTTON WINDOW"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);
	//(hwndButton, iCmdShow);


	// Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int) msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
		// Code
	switch (iMsg)
	{
		case WM_CREATE :
			AddMenu(hwnd);
			//Button 
			//CreateWindowEx(WS_EX_PALETTEWINDOW, "BUTTON", "Ok", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 175, 260, 140, 20, hwnd, (HMENU) 1, NULL, NULL);
			//CreateWindow(TEXT("button"), TEXT("Ok"),  WS_VISIBLE | WS_CHILD , 100, 100, 90, 30, hwnd, (HMENU) 1, NULL, NULL);
    		//CreateWindowEx(NULL, TEXT("Edit"),NULL, WS_CHILD | WS_VISIBLE  | WS_BORDER , 10, 10, 150, 20, hwnd, (HMENU) 1, NULL, NULL);
		break;

		case WM_COMMAND:
        	// MessageBox(NULL, TEXT("Hello World"), TEXT("MessageBox Title"), 0);
			switch(wParam)
			{
				case FILE_MENU_EXIT :
					DestroyWindow(hwnd);
				break;

				case FILE_MENU_NEW :
					MessageBeep(MB_ICONINFORMATION);
					break;
			}
        break;
        

		case WM_DESTROY :
			PostQuitMessage(0);
		break;

		default :
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


void AddMenu(HWND hwnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, NULL, "Submenu Item"); 

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New"); 
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL,NULL); 
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");


	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");


	SetMenu(hwnd, hMenu);
}

