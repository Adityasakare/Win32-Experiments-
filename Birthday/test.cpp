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
    int wmId, wmEvent;
    HDC hdc;
    RECT rc;
    PAINTSTRUCT ps;
    HBRUSH hbrush;
    static int iPaintFlag = 0;  
    TCHAR str[] = TEXT("Hello World !!! ");

    // Code
    switch (iMsg)
    {
        case WM_CREATE :
            SetTimer(hwnd, ID_TIMER1, 300, NULL);
            break;

        case WM_TIMER :
            KillTimer(hwnd, ID_TIMER1);
            iPaintFlag++;
            if (iPaintFlag >= 8)
                iPaintFlag = 0;
            InvalidateRect(hwnd, NULL, TRUE);
            SetTimer(hwnd, ID_TIMER1, 1000, NULL);
            break;

        case WM_PAINT :
            HBRUSH hbrush1;
            HFONT hFont;
            RECT rect;
            GetClientRect(hwnd, &rc);
            hdc = BeginPaint(hwnd, &ps);

            if (iPaintFlag == 1)
            {
                
            hFont = CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
            SelectObject(hdc, hFont);
            
            //Sets the coordinates for the rectangle in which the text is to be formatted.
            SetRect(&rect, 100,200,900,800);
            SetTextColor(hdc, RGB(0,0,0));
            DrawText(hdc, TEXT("Drawing Text with Impact"), -1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                hbrush = CreateSolidBrush(RGB(255, 0, 0));  //red
            
        }
            else if (iPaintFlag == 2)
            {
                hbrush = CreateSolidBrush(RGB(0, 255, 0));  //green
            
            hFont = CreateFont(36,20,-300,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));
            SelectObject(hdc,hFont);
            
            //Sets the coordinates for the rectangle in which the text is to be formatted.
            SetRect(&rect, 100, 200, 900, 800);
            SetTextColor(hdc, RGB(0,128,0));
            DrawText(hdc, TEXT("Drawing Text with Times New Roman"), -1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }

            else if (iPaintFlag == 3)
                hbrush = CreateSolidBrush(RGB(0, 0, 255));  //blue
            else if (iPaintFlag == 4)
                hbrush = CreateSolidBrush(RGB(0, 255, 255));    //ciyan 
            else if (iPaintFlag == 5)
                hbrush = CreateSolidBrush(RGB(255, 0, 255));
            else if (iPaintFlag == 6)
                hbrush = CreateSolidBrush(RGB(255, 255, 0));    //yello
            else if (iPaintFlag == 7)
                hbrush = CreateSolidBrush(RGB(0, 0, 0));    //black
            else if (iPaintFlag == 8)
                hbrush = CreateSolidBrush(RGB(255, 255, 255));  //white
            else

                hbrush = CreateSolidBrush(RGB(0, 0, 0));    //black 

            //SetBkColor(hdc, );
            
            SelectObject(hdc, hbrush);
            FillRect(hdc, &rc, hbrush);
            DeleteObject(hbrush);

            //Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
            //The width, when set to 0, will cause the font mapper to choose the closest matching value.
            //The font face name will be Impact.
            
            

            //Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
            //The width, when set to 20, will cause the font mapper to choose a font which, in this case, is stretched.
            //The font face name will be Times New Roman.  This time nEscapement is at -300 tenths of a degree (-30 degrees)
            
            
                
            //Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
            //The width, when set to 10, will cause the font mapper to choose a font which, in this case, is compressed. 
            //The font face name will be Arial. This time nEscapement is at 250 tenths of a degree (25 degrees)
            hFont = CreateFont(36,10,250,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, VARIABLE_PITCH,TEXT("Arial"));
            SelectObject(hdc,hFont);

            //Sets the coordinates for the rectangle in which the text is to be formatted.
            //SetRect(&rect, 500, 200, 1400, 600);
            SetTextColor(hdc, RGB(0,0,255));
            DrawText(hdc, TEXT("Drawing Text with Arial"), -1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            DeleteObject(hFont);  
            //SetTextColor(hdc, RGB(0, 255, 0));
            //DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            
            EndPaint(hwnd, &ps);

            break;

        case WM_DESTROY :
            PostQuitMessage(0);
        break;

        default :
            break;
    }
    return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
