/*
	Window Differnt fonts without Differnt Background colours (ONLY BLACK)
*/
#include <windows.h>
#include <tchar.h>

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
	HBRUSH hbrush;
	RECT rect;
    HFONT hFont;
	static int iPaintFlag = 0;	
	TCHAR str[] = TEXT("Happy Birthday Win32 !!! ");
	HFONT hOldFont;


	// Code
	switch (iMsg)
	{
		case WM_CREATE :
			SetTimer(hwnd, ID_TIMER1, 1000, NULL);
			break;

		case WM_TIMER :
			KillTimer(hwnd, ID_TIMER1);

			iPaintFlag++;
			if (iPaintFlag >= 9)
				iPaintFlag = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 1000, NULL);
			break;

		case WM_PAINT :

			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			if (iPaintFlag == 1)
			{
				//hbrush = CreateSolidBrush(RGB(255, 0, 0));	//red
				
				hFont = CreateFont(48,10,0,0,FW_BOLD,TRUE,FALSE,FALSE,CHINESEBIG5_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, FF_ROMAN,TEXT("Arial"));
			
				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 0));
				SelectObject(hdc,hFont);

				SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

				//SelectObject(hdc, hbrush);
				//FillRect(hdc, &rc, hbrush);

				DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            	DeleteObject(hFont);
            	

			}

			else if (iPaintFlag == 2)
			{
				//hbrush = CreateSolidBrush(RGB(0, 255, 0));	//green
				hFont = CreateFont(48,10,0,0,FW_DONTCARE,TRUE,FALSE,FALSE,HEBREW_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, FF_MODERN,TEXT("Arial"));
			
				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 0));
				SelectObject(hdc,hFont);

				SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

				//SelectObject(hdc, hbrush);
				//FillRect(hdc, &rc, hbrush);

				DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				//wsprintf(str, TEXT("Incrementing Order मराठी "));
				//TextOut(hdc, 5, 5, str, (int)_tcslen(str));
            	DeleteObject(hFont);
			}
			
			else if (iPaintFlag == 3)
			{
				//hbrush = CreateSolidBrush(RGB(0, 0, 255));	//blue
				hFont = CreateFont(48,10,0,0,FW_EXTRABOLD,TRUE,FALSE,FALSE,HEBREW_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,DRAFT_QUALITY, FF_SCRIPT,TEXT("Arial"));			
				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 0));
				SelectObject(hdc,hFont);

				SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

				//SelectObject(hdc, hbrush);
				//FillRect(hdc, &rc, hbrush);

				DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            	DeleteObject(hFont);
			}
			
			else if (iPaintFlag == 4)
			{
				//hbrush = CreateSolidBrush(RGB(0, 255, 255));	//ciyan 
				hFont = CreateFont(48, 10, 0, 0, FW_BOLD, FALSE,FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
    				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Broadway");
				
				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 0));
				
				SelectObject(hdc,hFont);

				SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

				//SelectObject(hdc, hbrush);
				//FillRect(hdc, &rc, hbrush);

				DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            	DeleteObject(hFont);			}
			
			else if (iPaintFlag == 5)
			{
				//hbrush = CreateSolidBrush(RGB(255, 0, 255));
				hFont = CreateFont(MulDiv(48, GetDeviceCaps(hdc, LOGPIXELSY), 72), 10, 0, 0, FW_NORMAL, 0, 0, 0, 
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Courier New");

				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 0));
				SelectObject(hdc,hFont);

				SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

				//electObject(hdc, hbrush);
				//FillRect(hdc, &rc, hbrush);

				DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            	DeleteObject(hFont);			
            }
			
			else if (iPaintFlag == 6)
			{
				//hbrush = CreateSolidBrush(RGB(255, 255, 0));	//yello
				hFont = CreateFontA(48, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");
				
				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 0));
				
				SelectObject(hdc,hFont);

				SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

				//SelectObject(hdc, hbrush);
				//FillRect(hdc, &rc, hbrush);

				DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            	DeleteObject(hFont);
            }
			
			else if (iPaintFlag == 7)
			{
				//hbrush = CreateSolidBrush(RGB(0, 0, 0));	//black
				hFont  = CreateFontA(48, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
				
				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 0));
				
				SelectObject(hdc,hFont);

				SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

				//SelectObject(hdc, hbrush);
				//FillRect(hdc, &rc, hbrush);

				DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            	DeleteObject(hFont);
            }
			else if (iPaintFlag == 8)
			{	
				//hbrush = CreateSolidBrush(RGB(255, 255, 255));	//white
				hFont = CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, FF_DECORATIVE,TEXT("Impact"));
				
				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 0));
				
				SelectObject(hdc,hFont);

				SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont, TRUE);

				//SelectObject(hdc, hbrush);
				//FillRect(hdc, &rc, hbrush);

				DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            	DeleteObject(hFont);
			}

			else

				hbrush = CreateSolidBrush(RGB(0, 0, 0));	//black	

			
			DeleteObject(hbrush);
			EndPaint(hwnd, &ps);
			break;

		case WM_LBUTTONDOWN :
			PlaySound(TEXT("HBD.wav"), NULL, SND_ASYNC | SND_FILENAME );
			break;
		case WM_DESTROY :
			PostQuitMessage(0);
		break;

		default :
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
