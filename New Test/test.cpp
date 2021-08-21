#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <cstdio>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
WNDCLASSEX wc;
MSG Msg;
wc.cbSize = sizeof(WNDCLASSEX);
wc.style = 0;wc.lpfnWndProc = WndProc;
wc.cbClsExtra = 0;
wc.cbWndExtra = 0;
wc.hInstance = hInstance;
wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
wc.hCursor = LoadCursor(NULL, IDC_ARROW);
wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
wc.lpszMenuName = NULL;
wc.lpszClassName = TEXT("myWindowClass");
wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
RegisterClassEx(&wc);
CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("myWindowClass"),TEXT("Display Text"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT,700, 300, NULL, NULL, hInstance, NULL);
while(GetMessage(&Msg, NULL, 0, 0) > 0)
{
DispatchMessage(&Msg);
}
return Msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
PAINTSTRUCT Ps;
HDC hdc;
SIZE size;
char str[100]="";
HFONT font;
HBRUSH hBrush;
TEXTMETRIC tm;
int y=0;
int x=0;
RECT rc;


switch(msg)
{
case WM_PAINT:
//text output using default font
GetClientRect(hwnd, &rc);

hdc = BeginPaint(hwnd, &Ps);
int hDCLast;
hDCLast=SaveDC(hdc);
sprintf(str,"Happy Birthday ");
DrawText(hdc, str, -1, &rc, DT_SINGLELINE );

//TextOutA(hdc,0,y,str,strlen(str));

//select ANSI_FIXED_FONT and output text
GetTextMetrics(hdc,&tm);
y=y+tm.tmHeight;//calculate new vertical coordinate using text metric
hBrush=(HBRUSH)GetStockObject(ANSI_FIXED_FONT);
SelectObject(hdc,hBrush);
sprintf(str,"ANSI_FIXED_FONT");
TextOutA(hdc,0,y,str,strlen(str));

//set text to red and output text
GetTextMetrics(hdc,&tm);
y=y+tm.tmHeight;
COLORREF newtextcolour;
newtextcolour=COLORREF RGB(255, 0, 0);
SetTextColor(hdc,newtextcolour);
sprintf(str,"ANSI_FIXED_FONT, colour red");
TextOutA(hdc,x,y,str,strlen(str));

//set text background to blue and output text
GetTextMetrics(hdc,&tm);
y=y+tm.tmHeight;
COLORREF newbkcolour;
newbkcolour=COLORREF RGB(0, 0, 255);
SetBkColor(hdc,newbkcolour);
sprintf(str,"ANSI_FIXED_FONT, colour red with blue background");
TextOutA(hdc,x,y,str,strlen(str));

//set text background to transparent and output text
GetTextMetrics(hdc,&tm);
y=y+tm.tmHeight;
SetBkMode(hdc,TRANSPARENT);
SelectObject(hdc,hBrush);
sprintf(str,"ANSI_FIXED_FONT, colour red transparent background");
TextOutA(hdc,0,y,str,strlen(str));

//select font Ariel 20 and output text
GetTextMetrics(hdc,&tm);
y=y+tm.tmHeight;
font = CreateFontA(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Ariel");
SelectObject(hdc,font);
sprintf(str,"ANSI_FIXED_FONT, colour red, transparent background,arial 20");
TextOutA(hdc,0,y,str,strlen(str));

//restore default font using saved value and output text
GetTextMetrics(hdc,&tm);
y=y+tm.tmHeight;
RestoreDC(hdc,hDCLast);
sprintf(str,"stock font restored using SaveDC/RestoreDC");
TextOutA(hdc,x,y,str,strlen(str));
GetTextMetrics(hdc,&tm);
y=y+tm.tmHeight;//calculate new vertical coordinate using text metric

//select font times new romans 30 and output text
int baseline;//used to caculate font baseline
font = CreateFontA(30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
SelectObject(hdc,font);
GetTextMetrics(hdc,&tm);
baseline=tm.tmAscent;
sprintf(str,"times new roman 30 statement 1");
TextOutA(hdc,x,y,str,strlen(str));
GetTextExtentPoint32A(hdc,str,strlen(str),&size);
x=x+size.cx;

//select font courier new 20 and output text
int baselinecourier;
font = CreateFontA(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");
SelectObject(hdc,font);
GetTextMetrics(hdc,&tm);
baselinecourier=baseline-tm.tmAscent;
sprintf(str,"Courier statement 2");
TextOutA(hdc,x,y+baselinecourier,str,strlen(str));
GetTextExtentPoint32A(hdc,str,strlen(str),&size);
x=x+size.cx;

//select font ariel 20 and output text
int baselineariel;
font = CreateFontA(10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Ariel");
SelectObject(hdc,font);
GetTextMetrics(hdc,&tm);
baselineariel=baseline-tm.tmAscent;
sprintf(str,"ariel 10 statement 3");
TextOutA(hdc,x,y+baselineariel,str,strlen(str));

EndPaint(hwnd, &Ps);
DeleteDC(hdc);
DeleteObject(font);
DeleteObject(hBrush);
break;
case WM_CLOSE:
DestroyWindow(hwnd);
break;
case WM_DESTROY:
PostQuitMessage(0);
break;
default:
return DefWindowProc(hwnd, msg, wParam, lParam);
}
return 0;
}