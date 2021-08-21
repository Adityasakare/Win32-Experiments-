#include <windows.h>
//#include <winmm.h>

// Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations
HWND CreateDTC(HWND hWnd)
{
    INITCOMMONCONTROLSEX icex;
    icex = { sizeof(icex), ICC_DATE_CLASSES };
    InitCommonControlsEx(&icex);

    return CreateWindowExW(0, DATETIMEPICK_CLASS, L"DateTime",
                           WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHOWNONE,
                           10, 10, 150, 25, hWnd, nullptr, hInst, nullptr);
}

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
	    static HWND hDTC = nullptr;
	    RECT rc;
	    HWND hMC;

	// Code
	switch (iMsg)
	{
		case WM_CREATE :
			hDTC = CreateDTC(hwnd);
        DateTime_SetMonthCalColor(hDTC, MCSC_BACKGROUND, RGB(0, 120, 250)); // blue
        DateTime_SetMonthCalColor(hDTC, MCSC_MONTHBK, RGB(120, 250, 0));    // green
			break;

case WM_NOTIFY:
        switch(((LPNMHDR)lParam)->code)
        {
        case DTN_DROPDOWN:
            hMC = DateTime_GetMonthCal(hDTC);
            
            MonthCal_GetMinReqRect(hMC, &rc);
            MoveWindow(hMC, 0, 0, (5 * rc.right) / 2, (3 * rc.bottom) / 2, FALSE);
            break;
        }
break;
    //...
    


	case WM_DESTROY :
		PostQuitMessage(0);
	break;

	default :
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
