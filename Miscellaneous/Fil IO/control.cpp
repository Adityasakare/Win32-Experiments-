#include <windows.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
//#include<unistd.h>
#include<fcntl.h>
#include <io.h>

#define FILE_MENU_NEW 1 
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4

// Global Function declerations
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void AddMenu(HWND);
void AddControl(HWND);

// Global Variable Declarations
HMENU hMenu;
HWND hName, hAge, hOut;

// Entry point functions
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Variable Declarations

	WNDCLASSEX wndclass;
	HWND hwnd;
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
						100,
						100,
						500,
						500,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

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
			AddControl(hwnd);
			break;

		case WM_COMMAND:
        	switch(wParam)
			{
				case FILE_MENU_EXIT :
					DestroyWindow(hwnd);
				break;

				case FILE_MENU_NEW :
					MessageBeep(MB_ICONINFORMATION);
				break;

				case  GENERATE_BUTTON :

					char name[30], age[10], out[100];
					char out2[30], fNmae[30];
					char FullName[8] = {"Name : "};
					char Description [15] = {"Description : "};

					int fd;
					HANDLE hFile;
					DWORD dwBytesWritten = 0;
					//LARGE_INTEGER  liDistanceToMove = sizeof(out2 + 80);

					GetWindowText(hName, name, 30);
					GetWindowText(hAge, age, 10);

					strcpy(out, name);

					strcat(out, " is ");
					strcpy(out2, out);
					strcpy(out, age);
					strcat(out, " years old.");
					strcat(out2, out);

					SetWindowText(hOut, out2);	

					strcpy(fNmae, name);
					strcat(fNmae, ".txt");

						hFile =  CreateFile(fNmae,                // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_NEW,             // create new file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template	

					
					//_lseek((int)hFile, sizeof(out2 + 50), NULL);
					//SetFilePointer(hFile, 10, NULL, FILE_CURRENT);
					WriteFile(hFile, FullName, sizeof(FullName), &dwBytesWritten, NULL);
					WriteFile(hFile, fNmae, sizeof(fNmae), &dwBytesWritten, NULL);
					SetFilePointer(hFile, 10, NULL, FILE_CURRENT);
					WriteFile(hFile, Description, sizeof(Description), &dwBytesWritten, NULL);
					WriteFile(hFile, out2, sizeof(out2), &dwBytesWritten, NULL);


						

									

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

	AppendMenu(hSubMenu, MF_STRING, NULL, "Submenu Menu"); 

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New"); 
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL,NULL); 
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");


	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");


	SetMenu(hwnd, hMenu);
}

void AddControl(HWND hwnd)
{
	CreateWindowW(L"static", L"Name :", WS_VISIBLE | WS_CHILD, 100, 50, 98, 38, hwnd,
					NULL, NULL, NULL);
	hName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 98, 38, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"Age :", WS_VISIBLE | WS_CHILD, 100, 90, 98, 38, hwnd,
					NULL, NULL, NULL);
	hAge = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 98, 38, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"button", L"Generate", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 140, 98, 38, hwnd,
					(HMENU)GENERATE_BUTTON, NULL, NULL);

	hOut = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 300, 200, hwnd,
					NULL, NULL, NULL);





}

