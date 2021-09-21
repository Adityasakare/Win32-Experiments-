/*
	Seprate Strings 
*/
#include <windows.h>
#include <tchar.h>

#define ID_TIMER1 101
// Global Function Declarations
void OnPaint1(HWND);
void OnPaint2(HWND);
void Normal(HWND hwnd);


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declarations
 int width;
 int height;
 RECT rect;
 PAINTSTRUCT ps;
 HDC hdc;
 TCHAR str1[] = TEXT("Happy ");
 TCHAR str2[] = TEXT("Birthday");
 TCHAR str3[] = TEXT("Piyush Sir!!!");

// Font Decleartions
 HFONT hFont1 = CreateFont(28,10,0,0,FW_BOLD,TRUE,FALSE,FALSE,CHINESEBIG5_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, FF_ROMAN,TEXT("Arial"));

 HFONT hFont2 = CreateFont(28,10,0,0,FW_DONTCARE,TRUE,FALSE,FALSE,HEBREW_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, FF_MODERN,TEXT("Arial"));

 HFONT hFont3 = CreateFont(28,10,0,0,FW_EXTRABOLD,TRUE,FALSE,FALSE,HEBREW_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,DRAFT_QUALITY, FF_SCRIPT,TEXT("Arial"));

 HFONT hFont4 = CreateFont(28, 10, 0, 0, FW_BOLD, FALSE,FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
    				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Broadway");

HFONT hFont5 = CreateFont(MulDiv(28, GetDeviceCaps(hdc, LOGPIXELSY), 72), 10, 0, 0, FW_NORMAL, 0, 0, 0, 
					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Courier New");

HFONT hFont6 = CreateFontA(28, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");

HFONT hFont7 = CreateFontA(28,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");

HFONT hFont8 = CreateFont(28,10,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, FF_DECORATIVE,TEXT("Impact"));


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
		TEXT("Birthday Window "),
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
	TCHAR str4[] = TEXT("Happy Birthday Piyush Sir !!!");
	
	static int iPaintFlag = 0;
	// Code
	
	if(GetWindowRect(hwnd, &rc))
	{
  		 width = rc.right - rc.left;
  		 height = rc.bottom - rc.top;
	}

	switch (iMsg)
	{
		case WM_CREATE :

			
			SetTimer(hwnd, ID_TIMER1, 950, NULL);
			break;

		case WM_TIMER :
			KillTimer(hwnd, ID_TIMER1);
			hdc = BeginPaint(hwnd, &ps);
    			//for (int i = 0; i < 1000; i++)
    				//Rectangle (hdc, 8,  8+ i, 7 *8, 7 * 8);
			iPaintFlag++;
			if (iPaintFlag >= 50)
				break;

			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, ID_TIMER1, 950, NULL);
			break;

		case WM_PAINT :
		
			if (iPaintFlag == 1)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));	//Green
    			SetBkMode(hdc, TRANSPARENT);
    			

    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);

    			//SetTextColor(hdc, RGB(0, 255, 0));	//Green
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(255, 0, 0));	//Red
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(255, 255, 0));	//Yellow
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				  //Normal(hwnd);
			}
			else if(iPaintFlag == 2)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(255, 0, 0));	//red	
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);

    			//SetTextColor(hdc, RGB(0, 0, 255));	//Blue
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(0, 255, 255));	//Cyan
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(255, 0, 255));	//Magneta
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				//OnPaint2(hwnd);
			}
			else if(iPaintFlag == 3)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(173,255,47));	//green yellow
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);

    			//SetTextColor(hdc, RGB(255,69,0));	//orange red
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(173,255,47));	//green yellow
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(34,139,34));	//forest green
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				//OnPaint2(hwnd);
			}
			else if(iPaintFlag == 4)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(140,139,139));	//dark cyan
    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);

    			//SetTextColor(hdc, RGB(0,255,127));	//spring green
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(32,178,170));	//light sea green
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(140,139,139));	//dark cyan
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 5)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				
    			SetBkMode(hdc, TRANSPARENT);
    			SetTextColor(hdc, RGB(138,43,226));	//blue voilet
    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);

    			//SetTextColor(hdc, RGB(0,128,128));	//navy
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(138,43,226));	//blue voilet
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(30,144,255));	//	dodger blue
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 6)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				
    			SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(75,190,130));	//indigo
    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			//SetTextColor(hdc, RGB(139,0,139));	//dark magneta
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(75,190,130));	//indigo
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(205,133,63));	//peru
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 7)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				
    			SetBkMode(hdc, TRANSPARENT);
    			SetTextColor(hdc, RGB(244,164,96));	//sandy brown

    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			//SetTextColor(hdc, RGB(112,128,144));	//silent grey
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(188,143,143));	//rosy brown
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(244,164,96));	//sandy brown
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 8)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(128,0,128));	//purple
    			
    			SelectObject(hdc,hFont8);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont8, TRUE);
    			//SetTextColor(hdc, RGB(255,0,220));	//
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(188,143,143));	//rosy brown
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(244,164,96));	//sandy brown
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
    			/*
    			TextOut(hdc, (width/2) - 180, height / 2, str1, (int)_tcslen(str1));
    			//SetTextColor(hdc, RGB(255,248,220));	//crown silk
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			//SetTextColor(hdc, RGB(128,0,128));	//purple
    			TextOut(hdc, (width/2) + 180, height / 2, str3, (int)_tcslen(str3));
				*/
    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 9)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(165,42,42));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont8);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont8, TRUE);
    			SetTextColor(hdc, RGB(165,42,180));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont8);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont8, TRUE);
    			SetTextColor(hdc, RGB(100,160,42));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 10)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont8);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont8, TRUE);
    			SetTextColor(hdc, RGB(139,0,139));	//dark magneta
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(139,160,139));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont8);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont8, TRUE);
    			SetTextColor(hdc, RGB(255,0,50));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 11)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont8);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont8, TRUE);
    			SetTextColor(hdc, RGB(139,130,100));
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont8);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont8, TRUE);
    			SetTextColor(hdc, RGB(139,0,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(139,255,0));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 12)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(139,255,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(19,25,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(0,255,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 13)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(139,255,180));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont8);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont8, TRUE);
    			SetTextColor(hdc, RGB(139,155,0));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(255,50,139));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 14)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(139,0,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(139,255, 0));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(139,150,0));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 15)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(199,25,50));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(255,25,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(130,190,160));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 16)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(100,255,185));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(155,25,150));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(0,255,50));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 17)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(139,250,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(90,255,55));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(139,255,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 18)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 19)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(190,250,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(139,0,210));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(139,0,0));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 20)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(19,25,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(139,255,55));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(139,255,0));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}	
			else if(iPaintFlag == 21)	//17
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(39,55,50));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(255,255,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(139,255,0));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 22)	//19
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(139,200,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(139,200,45));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(255,0,50));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 23)	//18
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(255,250,50));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(150,255,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(180,250,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 24)	//16
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(139,200,250));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(250,255,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(0,255,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 25)	//18
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(130,255,250));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(10,255,60));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(139,25,250));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 26)	//15
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(139,130,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(255,25,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(39,255,250));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 27)	//14
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			//SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(139,255,60));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(139,25,160));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(100,190,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 28)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont7);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont7, TRUE);
    			SetTextColor(hdc, RGB(130,20,250));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont5);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont5, TRUE);
    			SetTextColor(hdc, RGB(200,255,0));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont6);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont6, TRUE);
    			SetTextColor(hdc, RGB(55,200,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 29)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(13,200,0));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(15,200,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(190,20,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 30)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(255,200,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(50,200,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(19,200,240));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 31)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(39,20,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(13,20,55));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(139,200,55));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 32)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(99,230,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(155,96,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(139,255,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 33)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(139,190,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(13,210,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(139,150,55));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 34)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(1,190,55));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(110,140,251));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(102,120,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 35)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(121,154,241));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(124,125,25));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(255,200,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			
			else if(iPaintFlag == 36)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(142,20,254));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(19,20,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(99,140,210));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 37)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(50,21,250));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(144,100,250));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(150,40,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 38)	
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(245,240,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(13,250,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(139,20,25));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 39)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(225,20,25));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			SetTextColor(hdc, RGB(255,0,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(13,255,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 40)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(13,240,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(139,255,20));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(245,200,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 41)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(139,205,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(255,20,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(139,0,215));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 42)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(19,200,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(39,20,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(195,200,55));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 43)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(175,20,205));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(149,240,25));	

    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont2);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    			SetTextColor(hdc, RGB(251,204,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 44)
			{
				hdc = BeginPaint(hwnd, &ps);
        
   		 		GetClientRect(hwnd, &rect);
    			SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(139,200,255));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(139,20,25));	

    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    			SelectObject(hdc,hFont1);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    			SetTextColor(hdc, RGB(139,245,255));	
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));
				
				EndPaint(hwnd, &ps);
			}
			else if(iPaintFlag == 45)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			SetTextColor(hdc, RGB(13,20,55));	
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			SetTextColor(hdc, RGB(39,200,255));	
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			SetTextColor(hdc, RGB(255,200,255));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				//OnPaint2(hwnd);
			}
			else if(iPaintFlag == 46)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(255, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 47)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(255, 0, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				//OnPaint2(hwnd);
			}

			else if(iPaintFlag == 48)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(255, 255, 255));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 49)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(30,144,255));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);				
			}
			/*
			else if(iPaintFlag == 50)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				//OnPaint2(hwnd);
			}
			else if(iPaintFlag == 51)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 52)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				//OnPaint2(hwnd);
			}
			
			else if(iPaintFlag == 53)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 54)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				//OnPaint2(hwnd);
			}
			else if(iPaintFlag == 55)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			else if(iPaintFlag == 56)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont3);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				//OnPaint2(hwnd);
			}
			else if(iPaintFlag == 57)
			{
				GetClientRect(hwnd, &rc);
				hdc = BeginPaint(hwnd, &ps);
				SetTextColor(hdc, RGB(0, 255, 0));
    			SetBkMode(hdc, TRANSPARENT);

    			SelectObject(hdc,hFont4);
    			SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont4, TRUE);
    			TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    			TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    			TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    			EndPaint(hwnd, &ps);
				
			}
			*/


			
			


		break;

		case WM_DESTROY :
			PostQuitMessage(0);
		break;
		case WM_LBUTTONDOWN :
			PlaySound(TEXT("HBD2.wav"), NULL, SND_ASYNC | SND_FILENAME );

			break;


		default :
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

	//Widhth = 1025
	//height = 525

	void OnPaint2(HWND hwnd)
{
    hdc = BeginPaint(hwnd, &ps);
        
    GetClientRect(hwnd, &rect);
    SetTextColor(hdc, RGB(0, 255, 0));
    SetBkMode(hdc, TRANSPARENT);

    SelectObject(hdc,hFont1);
    SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);
    TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));


    SelectObject(hdc,hFont2);
    SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont2, TRUE);
    TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));


    SelectObject(hdc,hFont3);
    SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont3, TRUE);
    TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    /*
    TCHAR strlen_height[255];
    TCHAR strlen_width[255];

    wsprintf(strlen_width, TEXT("Width = %d and width / 2 %d") , width, width / 2);
    TextOut(hdc, 5, 5, strlen_width, (int)_tcslen(strlen_width));

    wsprintf(strlen_height, TEXT("Height = %d"),height);
    TextOut(hdc, 5, 25, strlen_height, (int)_tcslen(strlen_height));
	*/
    EndPaint(hwnd, &ps);   
    }

    void Normal(HWND hwnd)
    {
    	hdc = BeginPaint(hwnd, &ps);
        
    GetClientRect(hwnd, &rect);
    SetTextColor(hdc, RGB(0, 255, 0));
    SetBkMode(hdc, TRANSPARENT);

    SelectObject(hdc,hFont1);
    SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);

    TextOut(hdc, (width/2) - 75, height / 2, str1, (int)_tcslen(str1));
    TextOut(hdc, width/2, height / 2, str2, (int)_tcslen(str2));
    TextOut(hdc, (width/2) + 100, height / 2, str3, (int)_tcslen(str3));

    EndPaint(hwnd, &ps);
    }
