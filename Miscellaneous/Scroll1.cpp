#include <Windows.h>
 
 
 //Standard paradigm of WINDOWS program: define WINDOWS entry function WinMain
 //Register a window object
 //Define the attributes of the window, that is, the members of the WNDCLASS structure
 //Define the processing function corresponding to the window, namely WndProc callback function
 //Cycle the process message queue in WinMain
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("AppName");
	HWND   hwnd;
	MSG    msg;
	WNDCLASS   wndclass;
	int  cxclient, cyclient;
 
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.cbClsExtra = NULL;
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpfnWndProc = WndProc;
	wndclass.style = CS_HREDRAW|CS_VREDRAW;
 
	 //The window class needs to be registered before the window is created
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Need Windows NT"), TEXT(""),MB_HELP); 
		return 0;
	}
 
 
	 //A very useful function to get the screen properties, F12 can see the detailed usage, here is to get the width and height of the screen
	cxclient = GetSystemMetrics(SM_CXSCREEN);
	cyclient = GetSystemMetrics(SM_CYSCREEN);
 
	
	hwnd = CreateWindow(szAppName,
		 TEXT(""), //Window title, can be set to empty, TEXT() is a byte processing macro provided by Microsoft, when _UNICODE is set, it represents the UNICODE character, otherwise it is ASC11 character
		 WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, //The first macro has a title bar for the window, maximized, minimized, and exited, the latter two specify that the window has vertical and horizontal scroll bars
		 CW_USEDEFAULT,//cxclient, //Set the starting point of the window to be one third of the screen height and one third of the width
		CW_USEDEFAULT,//cyclient,
		 cxclient, //Set the window width and height to be one third of the screen
		cyclient,
		NULL,
		NULL,
		NULL,       //hInstance
		NULL);
 
	 //Show window after creating window
	ShowWindow(hwnd, TRUE);
	UpdateWindow(hwnd);
	 //The GetMessage message loop matches messages from the process message queue and converts them to the corresponding window. After the window receives the message, it calls the registered window processing function to process the translated message.
	 //It should be noted that if you want to get all messages from the process message queue, you need to set the second parameter to NULL, otherwise GetMessage can not get the WM_QUIT message, that is, you cannot exit the program.
	 //WM_QUIT belongs to any window of the process but not the process, only the second parameter NULL can be obtained, and the process exits after GetMessage obtains WM_QUIT
	while(GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
 
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static int cxClient, cyClient, cxBitmap, cyBitmap;
	static HBITMAP bitmap;
	static int iHScrollBarPos, iVScrollBarPos;
	
 
	switch(message)
	{
	case WM_CREATE:
		//BITMAP bmpinfo;
		//bitmap = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//if(!bitmap)
		//{
		//	MessageBox(hwnd, TEXT("Load Image Error"), TEXT("My Demo"), MB_ICONERROR);
		//}
		//GetObject(bitmap, sizeof(BITMAP), &bmpinfo);
		cxBitmap = 1000;
		cyBitmap = 1000;
		break;
	case WM_PAINT:
		HDC hdc, hdcSrc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		hdcSrc = CreateCompatibleDC(hdc);
		SelectObject(hdcSrc, bitmap);
		BitBlt(hdc, -iHScrollBarPos, -iVScrollBarPos, cxBitmap, cyBitmap, hdcSrc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		DeleteDC(hdcSrc);
		break;
	case WM_SIZE:
		 //Receive this message when the window size changes, F12 can view the meaning of the message parameters, msdn found a method to obtain the width and height of the new window
		cxClient = LOWORD(lparam);
		cyClient = HIWORD(lparam);
		 //Set the range of the scroll bar
		SetScrollRange(hwnd, SB_HORZ, 0, cxBitmap - cxClient, FALSE);
		SetScrollRange(hwnd, SB_VERT, 0, cyBitmap - cyClient, FALSE);
		 //Get the new position of the scroll bar, that is, determine whether the scroll bar exceeds the maximum range after the window size changes
		iHScrollBarPos = min(cxBitmap - cxClient, max(0, iHScrollBarPos));
		iVScrollBarPos = min(cyBitmap - cyClient, max(0, iHScrollBarPos));
		 //If the scroll bar exceeds the maximum range, reset the scroll bar range and refresh the window
		if(iHScrollBarPos != GetScrollPos(hwnd, SB_HORZ))
		{
			SetScrollPos(hwnd, SB_HORZ, iHScrollBarPos, TRUE);
			InvalidateRect(hwnd, NULL, FALSE);
		}
		if(iVScrollBarPos != GetScrollPos(hwnd, SB_VERT))
		{
			SetScrollPos(hwnd, SB_VERT, iVScrollBarPos, SB_VERT);
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;
	case WM_VSCROLL:
		 //Vertical scroll bar message, F12 view message can get detailed message parameters from MSDN
		switch(LOWORD(wparam))
		{
		case SB_LINEUP:
			 //Each scrolling picture changes 10 pixels
			iVScrollBarPos -= 10;
			break;
		case SB_LINEDOWN:
			iVScrollBarPos += 10;
			break;
		case SB_PAGEUP:
			 //Each time you turn the page, the entire client area is scrolled
			iVScrollBarPos -= cyClient;
			break;
		case SB_PAGEDOWN:
			iVScrollBarPos += cyClient;
			break;
		case SB_THUMBTRACK:
			iVScrollBarPos = HIWORD(wparam);
			break;
		default :
			break;
		}
		 //Determine whether the scroll bar after scrolling exceeds the maximum value or minimum value, if it exceeds the maximum value or minimum value, the maximum value or 0 is taken, otherwise it is equal to the current value
		iVScrollBarPos = min(cyBitmap - cyClient, max(0, iVScrollBarPos));
		 //If the scroll bar position changes, set the scroll bar position and refresh the screen
		if(iVScrollBarPos != GetScrollPos(hwnd, SB_VERT))
		{
			SetScrollPos(hwnd, SB_VERT, iVScrollBarPos, TRUE);
			 //Finally setting the parameter to FALSE can greatly reduce the screen flicker, you can try it.
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;
	case WM_HSCROLL:
		switch(LOWORD(wparam))
		{
		case SB_LINEUP:
			iHScrollBarPos -= 10;
			break;
		case SB_LINEDOWN:
			iHScrollBarPos += 10;
			break;
		case SB_PAGEUP:
			iHScrollBarPos -= cxClient;
			break;
		case SB_PAGEDOWN:
			iHScrollBarPos += cxClient;
			break;
		case SB_THUMBTRACK:
			iHScrollBarPos = HIWORD(wparam);
			break;
		default :
			break;
		}
		iHScrollBarPos = min(cxBitmap - cxClient, max(0, iHScrollBarPos));
		if(iHScrollBarPos != GetScrollPos(hwnd, SB_HORZ))
		{
			SetScrollPos(hwnd, SB_HORZ, iHScrollBarPos, TRUE);
			InvalidateRect(hwnd, NULL, FALSE);
		}
		break;
	case WM_DESTROY:
		 //Click the X in the upper right corner of the window, the system will send a WM_DESTROY message to the window, the message can not exit the window, the real exit window is the WM_QUIT message, call PostQuitMessage to send WM_QUIT message to the process message queue
		PostQuitMessage(1);
		DeleteObject(bitmap);
		return 0;
		break;
	default :
		break;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}