// cl.exe /c /EHsc Window.cpp
// link.exe Window.obj user32.lib gdi32.lib

/* Header File*/
#include <windows.h>
#include <stdlib.h>

/* Symbolic Constant */
#define FILE_MENU_NEW 1 
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4

/* typedefs */
typedef int status_t;

// Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddMenu(HWND);
void ControlPanel (HWND);
void StoreData(HWND);


// Global Variable Declarations
HWND hInput, hOutput;
HMENU hMenu;

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local Variable Declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	// Code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //API 
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	// Create Window in memeory
	hwnd = CreateWindow(szAppName,
		TEXT("Chat Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		490,			//width
		400,			// height
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

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Code
	PAINTSTRUCT ps;
	HDC hdc;
	//static status_t status_f = 0;
	
	switch (iMsg)
	{
		case WM_CREATE :
			hdc = BeginPaint(hwnd, &ps);
			AddMenu(hwnd);
			ControlPanel(hwnd);
			EndPaint(hwnd, &ps);
			
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);


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
					StoreData(hwnd);
				

				break;

			}
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

	AppendMenu(hSubMenu, MF_STRING, NULL, "Submenu Menu"); 

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New"); 
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL,NULL); 
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");


	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");


	SetMenu(hwnd, hMenu);
}

void ControlPanel (HWND hwnd)
{
	CreateWindowW(L"button", L"Submit", WS_VISIBLE | WS_CHILD | WS_BORDER, 370, 300, 98, 30, hwnd,
					(HMENU)GENERATE_BUTTON, NULL, NULL);

	hInput = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 300, 365, 30, hwnd,
							NULL, NULL, NULL);

	hOutput = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 3, 460, 280, hwnd,
							NULL, NULL, NULL);
}	

void StoreData(HWND hwnd)
{
		static status_t status_f = 0;

static HANDLE hFile;
	DWORD dwBytesWritten = 0, dwBytesRead = 0;

	char Out[15];
	char buf[15];
	memset(Out, 0, sizeof(Out));


					if (status_f == 0)
					{
						hFile =  CreateFile("chat.txt",                // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_NEW ,             // create new file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template	
					}
					
					GetWindowText(hInput, Out, 15);
					//WriteFile(hFile, Out, sizeof(Out), &dwBytesWritten, NULL);
					//SetFilePointer(hFile, 5, NULL, FILE_CURRENT);
					//SetWindowText(hOutput, Out);
					memset(Out, 0, sizeof(Out));
					//CloseHandle(hFile);
					status_f++;

					do
					{
						if (ReadFile(hFile, buf, 15, &dwBytesRead, NULL))
						{
							SetFilePointer(hFile, 5, NULL, FILE_BEGIN);
							//SetWindowText(hOutput, buf);
							MessageBox(hwnd, buf, TEXT("Msg"), MB_OK);
						}
					}while(dwBytesRead == 15);
}
