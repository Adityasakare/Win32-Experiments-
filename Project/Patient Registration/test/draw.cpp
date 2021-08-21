#include <windows.h>

#define IDC_COMBOBOX_TEXT 1000



const char ClassName[] = "MainWindowClass";

HWND hWndComboBox;



LRESULT CALLBACK WndProc( HWND    hWnd,

                          UINT    Msg,

                          WPARAM  wParam,          

                          LPARAM  lParam )

{

    switch (Msg)

    {

        case WM_CREATE:

        {

            hWndComboBox = CreateWindow("COMBOBOX", NULL,  WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 

            10, 10, 100, 800, hWnd, (HMENU)IDC_COMBOBOX_TEXT, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);



            if (!hWndComboBox)

                MessageBox(NULL, "ComboBox Failed.", "Error", MB_OK | MB_ICONERROR);



            SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"Item 1");

            SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"Item 2");

            SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"Item 3");

        }

        break; 



        case WM_COMMAND: 

        {

            switch(LOWORD(wParam))

            {

                case IDC_COMBOBOX_TEXT:

                {

                    switch(HIWORD(wParam))

                    {

                        // Handle notification code

                    }

                }

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



    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,cClassName,c"Combo Boxes", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,

    NULL, NULL,hInstance, NULL);



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
