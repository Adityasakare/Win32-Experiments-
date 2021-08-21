
#include <windows.h>
#define IDC_HSCROLLBAR 1000

#define IDC_VSCROLLBAR 1001

const char ClassName[] = "MainWindowClass";
HWND hWndHScrollBar;
HWND hWndVScrollBar;



LRESULT CALLBACK WndProc( HWND    hWnd,
                          UINT    Msg,
                          WPARAM  wParam,          
                         LPARAM  lParam )

{
    switch (Msg)
    {
        case WM_CREATE:
        {
            int ScrollBarWidth  = 15;
            int ScrollBarHeight = 15;
            RECT Rect;
            GetClientRect(hWnd, &Rect);


            hWndVScrollBar = CreateWindowEx(
            0,
            "SCROLLBAR", 
            NULL, 
            WS_VISIBLE | WS_CHILD | SBS_VERT,
            Rect.right - ScrollBarWidth, 
            0, 
            ScrollBarWidth, 
            Rect.bottom - ScrollBarHeight, 
            hWnd, 
            (HMENU)IDC_VSCROLLBAR, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndVScrollBar)
                MessageBox(NULL, "Vertical Scroll Bar Failed.", "Error", MB_OK | MB_ICONERROR);
            hWndHScrollBar = CreateWindowEx(
            0,
            "SCROLLBAR", 
            NULL, 
            WS_VISIBLE | WS_CHILD | SBS_HORZ,
            0,
            Rect.bottom - ScrollBarHeight, 
            Rect.right - ScrollBarWidth, 
            ScrollBarHeight, 
            hWnd, 
            (HMENU)IDC_HSCROLLBAR, 
            (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
            NULL);

            if (!hWndHScrollBar)
                MessageBox(NULL, "Horizontal Scroll Bar Failed.", "Error", MB_OK | MB_ICONERROR);

            SetScrollRange(hWndVScrollBar, SB_CTL, 0, 100, TRUE);
            SetScrollRange(hWndHScrollBar, SB_CTL, 0, 100, TRUE);
        }
        break; 

        case WM_HSCROLL:
        {
            switch ((int)LOWORD(wParam))
            {
                case SB_LINEUP:
                    SetScrollPos((HWND)lParam, SB_CTL, 0, TRUE);
                break;

                case SB_LINEDOWN:
                    SetScrollPos((HWND)lParam, SB_CTL, 100, TRUE);
                break;
            }
            return 0;
        }
        break;

        case WM_VSCROLL:
        {
            switch ((int)LOWORD(wParam))
            {
                case SB_LINEUP:
                    SetScrollPos((HWND)lParam, SB_CTL, 0, TRUE);
                break;

                case SB_LINEDOWN:
                    SetScrollPos((HWND)lParam, SB_CTL, 100, TRUE);
                break;
            }
            return 0;
        }
        break;
















        case WM_CLOSE:
            DestroyWindow(hWnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return (DefWindowProc(hWnd, Msg, wParam, lParam));

    }
    return 0;
}



INT WINAPI WinMain( HINSTANCE  hInstance,
                    HINSTANCE  hPrevInstance,
                    LPSTR      lpCmdLine,
                    INT        nCmdShow )

{

    WNDCLASSEX    wc;
    wc.cbSize           = sizeof(WNDCLASSEX);
    wc.style            = 0;
    wc.lpfnWndProc      = (WNDPROC)WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(NULL,IDI_APPLICATION);
    wc.hIconSm          = LoadIcon(NULL,IDI_APPLICATION);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = ClassName;

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Failed To Register The Window Class.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND    hWnd;
    hWnd = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    ClassName,
    "Scroll Bars",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    1377,
    700,
    NULL,
    NULL,
    hInstance,
    NULL);

    if (!hWnd)
    {
        MessageBox(NULL, "Window Creation Failed.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }



    ShowWindow(hWnd, SW_SHOW);

    UpdateWindow(hWnd);

    MSG    Msg;
    while (GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
