#include <windows.h>
#include <gdiplus.h>
#include <wingdi.h>

// Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


void onpaint (HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Bitmap bmp(L"cake.jpg");
			gf.DrawImage(&bmp, 430, 10);

}

// Global Variable Declarations

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Local Variable Declarations
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
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
	TCHAR str[] = TEXT("Hello World !!! ");

	// Code
	switch (iMsg)
	{

		case WM_PAINT :

			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			onpaint(hdc);
    					SetBkColor(hdc, RGB(0, 0, 0));
			SetTextColor(hdc, RGB(0, 255, 0));
			DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			//for (int i = 0; i < 1000; i++)
    				//Rectangle (hdc, i, 8, 7, 7 * 8);

			EndPaint(hwnd, &ps);
			PlaySound(TEXT ("HBD.wav"), NULL, SND_ASYNC | SND_FILENAME);
						break;

		case WM_DESTROY :
			PostQuitMessage(0);
		break;

		default :
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
