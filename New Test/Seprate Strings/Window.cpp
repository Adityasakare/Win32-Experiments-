/*
	Seprate Strings 
*/
#include <windows.h>
#include <tchar.h>
// Global Function Declarations
void OnPaint1(HWND);
void OnPaint2(HWND);


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations
 int width;
 int height;

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	// Create Window in memeory
	hwnd = CreateWindow(szAppName,
		TEXT("APS : My First Window"),
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
	//Varible declaration
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	int i;
	TCHAR str1[] = TEXT("Happy");
	TCHAR str2[] = TEXT("Birthday");
	TCHAR str3[] = TEXT("Win32 !!!");
	// Code
	
	if(GetWindowRect(hwnd, &rc))
	{
  		 width = rc.right - rc.left;
  		 height = rc.bottom - rc.top;
	}

	switch (iMsg)
	{

		case WM_PAINT :

					OnPaint2(hwnd);
					//OnPaint1(hwnd);


			
			
						/*
			rc.left = 40;
			rc.top = 10;
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(0, 255, 0));
			DrawText(hdc, str1, -1, &rc, DT_SINGLELINE | DT_NOCLIP);
			//DrawText(hdc, str2, -1, &rc, DT_SINGLELINE);
			EndPaint(hwnd, &ps);
			*/
	
			break;

		case WM_DESTROY :
			PostQuitMessage(0);
		break;

		default :
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

	void OnPaint1(HWND hWnd)
{
    RECT  rect;
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    TCHAR str1[] = TEXT("Hello ");

    GetClientRect(hWnd, &rect);
    SetTextColor(hdc, RGB(0xFF, 0x00, 0x00));
    SetBkMode(hdc, TRANSPARENT);
    rect.left = width / 2;
    rect.top = height / 2;
    //DrawText(hdc, str1, -1, &rect, DT_SINGLELINE | DT_VCENTER);
    TextOut(hdc, width/2, height/2, str1, (int)_tcslen(str1));

    //SelectObject(hdc, oldPen);
    //DeleteObject(hPen);
    EndPaint(hWnd, &ps);
}

	//Widhth = 1025
	//height = 525

	void OnPaint2(HWND hWnd)
{
    RECT  rect;
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    TCHAR strlen_height[255];
    TCHAR strlen_width[255];
    TCHAR str1[] = TEXT("Happy ");
    TCHAR str2[] = TEXT("Birthday");
    TCHAR str3[] = TEXT("Win32 !!!");

    GetClientRect(hWnd, &rect);
    SetTextColor(hdc, RGB(0, 255, 0));
    SetBkMode(hdc, TRANSPARENT);
    /*
    wsprintf(strlen_width, TEXT("Width = %d and width / 2 %d") , width, width / 2);
    TextOut(hdc, 5, 5, strlen_width, (int)_tcslen(strlen_width));

    wsprintf(strlen_height, TEXT("Height = %d"),height);
    TextOut(hdc, 5, 25, strlen_height, (int)_tcslen(strlen_height));
	*/

    TextOut(hdc, (width/2) - 49, height / 2, str1, (int)_tcslen(str1));
    TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    TextOut(hdc, (width/2) + 63, height / 2, str3, (int)_tcslen(str3));

    //SelectObject(hdc, oldPen);
    //DeleteObject(hPen);
    EndPaint(hWnd, &ps);
}
