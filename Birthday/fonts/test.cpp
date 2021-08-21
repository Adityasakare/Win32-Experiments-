#include <windows.h>

#define ID_TIMER1 101

// Global Function Declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations

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
	TCHAR str[] = TEXT("Happy Birthday Win32 !!! ");
	HFONT hFont;
	RECT rect;
	HBRUSH hbrush;
	static int iFontFlag = 0;


	// Code
	switch (iMsg)
	{
		case WM_CREATE :
			SetTimer(hwnd, ID_TIMER1, 300, NULL);
        	break;

        case WM_TIMER :
        	KillTimer(hwnd, ID_TIMER1);
        	iFontFlag++;
        	if (iFontFlag >= 5)
        		iFontFlag = 0;
        	InvalidateRect(hwnd, NULL, TRUE);
        	SetTimer(hwnd, ID_TIMER1, 1000, NULL);
        	break;

		case WM_PAINT :

		if (iFontFlag == 1)
		{
        	hbrush = CreateSolidBrush(RGB(255, 0, 0));	//red

		hFont = CreateFont(49,10,50,0,FW_DONTCARE,TRUE,FALSE,FALSE,HEBREW_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, VARIABLE_PITCH,TEXT("Arial"));
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			SetBkColor(hdc, RGB(255, 0, 255));
			SetTextColor(hdc, RGB(0, 255, 0));
			SelectObject(hdc,hFont);
			
			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);

			DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

						
			//SetTextColor(hdc, RGB(255,0,0));
            //DrawText(hdc, TEXT("Drawing Text with Arial"), -1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            DeleteObject(hFont);	

			
        }
        else if (iFontFlag == 2)
        {
        	hbrush = CreateSolidBrush(RGB(255, 0, 255));	//red

		hFont = CreateFont(49,10,50,0,FW_DONTCARE,TRUE,FALSE,FALSE,HEBREW_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, VARIABLE_PITCH,TEXT("Arial"));
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			SetBkColor(hdc, RGB(255, 0, 255));
			SetTextColor(hdc, RGB(0, 255, 0));
			SelectObject(hdc,hFont);
			
			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);

			DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

						
			//SetTextColor(hdc, RGB(255,0,0));
            //DrawText(hdc, TEXT("Drawing Text with Arial"), -1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            DeleteObject(hFont);

        }
        else if (iFontFlag == 3)
        {
        	hbrush = CreateSolidBrush(RGB(0, 255, 255));	//red

		hFont = CreateFont(49,10,50,0,FW_EXTRABOLD,TRUE,FALSE,FALSE,HEBREW_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, FF_SCRIPT,TEXT("Arial"));
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			SetBkColor(hdc, RGB(255, 0, 255));
			SetTextColor(hdc, RGB(0, 255, 0));
			SelectObject(hdc,hFont);
			
			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);

			DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

						
			//SetTextColor(hdc, RGB(255,0,0));
            //DrawText(hdc, TEXT("Drawing Text with Arial"), -1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            DeleteObject(hFont);

        }
        else if (iFontFlag == 4)
        {
        	hbrush = CreateSolidBrush(RGB(255, 255, 0));	//red

		hFont = CreateFont(49,10,50,0,FW_ULTRABOLD,TRUE,FALSE,FALSE,HEBREW_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, FF_DECORATIVE,TEXT("Arial"));
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			SetBkColor(hdc, RGB(255, 0, 255));
			SetTextColor(hdc, RGB(0, 255, 0));
			SelectObject(hdc,hFont);
			
			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

			SelectObject(hdc, hbrush);
			FillRect(hdc, &rc, hbrush);

			DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

						
			//SetTextColor(hdc, RGB(255,0,0));
            //DrawText(hdc, TEXT("Drawing Text with Arial"), -1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            DeleteObject(hFont);

        }

        	
			DeleteObject(hbrush);

			EndPaint(hwnd, &ps);
			break;
			
			case WM_DESTROY :
				PostQuitMessage(0);
				break;

		case WM_CHAR :
			switch (LOWORD(wParam))
			{
				case 'R' :
				case 'r' :
					iPaintFlag = 1;
					//PlaySound(TEXT ("HBD.wav"), NULL, SND_FILENAME);
					//InvalidateRect(hwnd, NULL, TRUE);
					break;
			}
			break;
		default :
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
