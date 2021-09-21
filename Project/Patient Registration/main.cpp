#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <commctrl.h>
#include <string.h>
#include <windowsx.h>

#include "window.h"


// Global Function declerations
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void AddMenu(HWND);
void PatientForm(HWND);
void TitleName(HWND);
void LoadImage();
void Seprator(HWND);
HWND CreateDTC(HWND);
void Address(HWND);
void ScrollBar(HWND);
void StoreData();
void CurrentDate(LPVOID);


// Global Variable Declarations
HMENU hMenu;
HWND hName, hAge, hOut, hOccupation, hReligion;
HWND hAddress, hCity, hPincode, hCountry, hState, hNationality, hBirth;
HWND hTel, hOffice, hMobile1, hMobile2, hEmail;
HWND hLogo, hBarcode;
HBITMAP hLogoImage, hBarcodeImage;
HWND hMarriedButton, hSingleButton, hWidowedButton, hDivorcedButton;
HWND hMale, hFemale, hOther;
HWND hWndHScrollBar;
HWND hWndVScrollBar;
TCHAR cMaritalStatus[11];
TCHAR Date[11];

 HFONT hFont1 = CreateFont(12,5,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_CHARACTER_PRECIS,
                CLIP_TT_ALWAYS,CLEARTYPE_QUALITY, FF_DECORATIVE,TEXT("Arial"));

// Entry point functions

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Variable Declarations

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName [] = TEXT("MyWindow");
	

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	RegisterClassEx(&wndclass);

	//Create window in memory
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,szAppName,
						TEXT("Patient Registration Form"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						1200,
						900,
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

	return ((int) msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hDTC = NULL;
    RECT Rect;
    int MsgBoxID;	


	switch (iMsg)
	{
		case WM_PAINT :
			TitleName(hwnd);
			CurrentDate((LPVOID)hwnd);
			//Seprator(hwnd);
		break;

		case WM_CREATE :
			LoadImage();
			AddMenu(hwnd);
			PatientForm(hwnd);
			Address(hwnd);
			//ScrollBar(hwnd);
			break;
		
		case WM_COMMAND:
        	switch(wParam)  
			{
				case FILE_MENU_EXIT :
					DestroyWindow(hwnd);
				break;

				case FILE_MENU_NEW :
					MessageBeep(MB_ICONINFORMATION);
				break;

				case SUBMIT_BUTTON :
        			StoreData();
        			MsgBoxID = MessageBox(hwnd, "Your Details are Saved","Message Box", MB_OK);
        			
        			switch(MsgBoxID)
        			{
        				case IDOK :
        					PostQuitMessage(0);
        				break;
        			}
        			break;
			}
        break;
       
		case WM_DESTROY :
			PostQuitMessage(0);
		break;

		default :
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

//////////////////////////////////////////////////////////////////////////////////////////
//	Function Name : AddMenu
//	Input:			main Handle
//	Output:			void 
//	Description:	Used to display the menubar made for understanding of menus and submenu
//	Author:			Aditya Sakare
////////////////////////////////////////////////////////////////////////////////////////////
void AddMenu(HWND hwnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, NULL, "Submenu Menu"); 

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New"); 
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL,NULL); 
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");


	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");


	SetMenu(hwnd, hMenu);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Function Name : TitleName
//	Input:			main Handle
//	Output:			void 
//	Description:	Used to display the Title of the Form i.e Hospital Name, Title Name, Address, Patient Title
//					and window for image
//	Author:			Aditya Sakare
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TitleName(HWND hwnd)
{
	RECT rc;
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR HospitalName[] = {"X.Y.Z NATIONAL HOSPITAL & MEDICAL RESEARCH CENTER"};
	TCHAR TitleName[] = {"(Establish & managed by the National Health & Education Society)"};
	TCHAR Address[] = {"Veer Savarkar Marg, Mahim, Mumbai- 400 016.  Tel: 244 1515, 2445 2222 Fax-2444 9157"};
	TCHAR PateintTitle[] = {"NEW PATIENT REGISTRATION FORM"};

	GetClientRect(hwnd, &rc);
	hdc = BeginPaint(hwnd, &ps);
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 415, 20, HospitalName, (int)_tcslen(HospitalName));
	TextOut(hdc, 420, 35, TitleName, (int)_tcslen(TitleName));
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 50, 100, PateintTitle, (int)_tcslen(PateintTitle));


	SelectObject(hdc,hFont1);
    SendMessage(hwnd, WM_SETFONT, (LPARAM)hFont1, TRUE);

	TextOut(hdc, 417, 55, Address, (int)_tcslen(Address));

	
	EndPaint(hwnd, &ps);

	hLogo = CreateWindowW(L"static", NULL , WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 20, NULL, NULL, hwnd,
					NULL, NULL, NULL);
	SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hLogoImage);

	//CreateWindowW(L"static", L"Barcode", WS_VISIBLE | WS_CHILD, 980, 100, 60, 30, hwnd,
	//				NULL, NULL, NULL);

	hBarcode = CreateWindowW(L"static", NULL , WS_VISIBLE | WS_CHILD | SS_BITMAP, 800, 90, NULL, NULL, hwnd,
					NULL, NULL, NULL);
	SendMessageW(hBarcode, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hBarcodeImage);

	}
//////////////////////////////////////////////////////////////////////////////////////////
//	Function Name : LoadImage
//	Input:			main Handle
//	Output:			void 
//	Description:	Used to initised the LoadImage into respective handles
//	Author:			Aditya Sakare
////////////////////////////////////////////////////////////////////////////////////////////
void LoadImage()
{
	hLogoImage = (HBITMAP)LoadImageW(NULL, L"res//img//image.bmp", IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
	hBarcodeImage = (HBITMAP)LoadImageW(NULL, L"res//img//Barcode.bmp", IMAGE_BITMAP, 200, 40, LR_LOADFROMFILE);
}

//////////////////////////////////////////////////////////////////////////////////////////
//	Function Name : Seprator
//	Input:			main Handle
//	Output:			void 
//	Description:	Used to display seprator
//	Author:			Aditya Sakare
////////////////////////////////////////////////////////////////////////////////////////////

void Seprator(HWND hwnd)
{	
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hLinePen;
	COLORREF qLineColor;
	HPEN hPenOld;

	hdc = BeginPaint(hwnd, &ps);
	qLineColor = RGB(0, 0, 0);
	hLinePen = CreatePen(PS_SOLID, 7, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);

	MoveToEx(hdc, 0, 90, NULL);
	LineTo(hdc, 1366,90);
	SelectObject(hdc, hPenOld);
	DeleteObject(hLinePen);
	EndPaint(hwnd, &ps);
}

//////////////////////////////////////////////////////////////////////////////////////////
//	Function Name : PatinetForm
//	Input:			main Handle
//	Output:			void 
//	Description:	Used to display  & handle the contains of Form i.e Name, age, date 
//	Author:			Aditya Sakare
////////////////////////////////////////////////////////////////////////////////////////////

void PatientForm(HWND hwnd)
{
	HWND hWndComboBox;
	CreateWindowW(L"static", L"Date", WS_VISIBLE | WS_CHILD, 50, 130, 40, 20, hwnd,
					NULL, NULL, NULL);

	//CreateWindowW(L"static", L"Number", WS_VISIBLE | WS_CHILD, 1050, 130, 45, 20, hwnd,
	//				NULL, NULL, NULL);

	CreateWindowW(L"static", L"Name", WS_VISIBLE | WS_CHILD, 50, 180, 40, 20, hwnd,
					NULL, NULL, NULL);

	hWndComboBox = CreateWindow("COMBOBOX", NULL,  WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 

            120, 180, 100, 800, hwnd, (HMENU)IDC_COMBOBOX_TEXT, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

			SendMessage(GetDlgItem(hwnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"Mr.");

            SendMessage(GetDlgItem(hwnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"Mrs.");

            SendMessage(GetDlgItem(hwnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)"Dr. ");

   hName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 180, 750, 25, hwnd,
					NULL, NULL, NULL);

   CreateWindowW(L"static", L"LAST NAME", WS_VISIBLE | WS_CHILD, 270, 160, 80, 20, hwnd,
					NULL, NULL, NULL);

   CreateWindowW(L"static", L"FIRST NAME", WS_VISIBLE | WS_CHILD, 470, 160, 90, 20, hwnd,
					NULL, NULL, NULL);

   CreateWindowW(L"static", L"LAST NAME", WS_VISIBLE | WS_CHILD, 770, 160, 80, 20, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"Date of birth", WS_VISIBLE | WS_CHILD, 50, 230, 88, 20, hwnd,
					NULL, NULL, NULL);

	hBirth = CreateWindowW(L"edit", L"00/00/0000", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 230, 90, 20, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"Age", WS_VISIBLE | WS_CHILD, 860, 230, 38, 20, hwnd,
					NULL, NULL, NULL);

	hAge = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 900, 230, 40, 20, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"Marital Status", WS_VISIBLE | WS_CHILD, 50, 280, 90, 20, hwnd,
					NULL, NULL, NULL);


	hMarriedButton = CreateWindowW(L"BUTTON", L"Married", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON , 240, 280, 75, 20, hwnd, 
                    NULL, NULL, NULL);

	hSingleButton = CreateWindowW(L"BUTTON", L"Single", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 460, 280, 60, 20, hwnd, 
                    NULL, NULL, NULL);

	hWidowedButton = CreateWindowW(L"BUTTON", L"Widowed", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 660, 280, 80, 20, hwnd, 
                    NULL, NULL, NULL);

	hDivorcedButton = CreateWindowW(L"BUTTON", L"Divorced", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 860, 280, 80, 20, hwnd, 
                    NULL, NULL, NULL);
	
	 UINT t=SendMessage(hMarriedButton,BM_GETCHECK,0, 0);

	 if (t == BST_CHECKED)
	 	 wsprintf(cMaritalStatus, TEXT("Married"));
	/*
	//memset(cMaritalStatus, 0, sizeof(cMaritalStatus));
	if( Button_GetCheck(hMarriedButton) == BST_CHECKED)
	{
		 wsprintf(cMaritalStatus, TEXT("Married")); //cMaritalStatus = {"Married"}; 
	}
	else if((Button_GetState(hSingleButton)) == BST_CHECKED)
	{
		wsprintf(cMaritalStatus, TEXT("Single")); //cMaritalStatus = {"Single"};
	}
	else if((Button_GetState(hWidowedButton)) == BST_CHECKED)
	{
		wsprintf(cMaritalStatus, TEXT("Widowed")); //cMaritalStatus = {"Widowed"};
	}
	else if((Button_GetState(hDivorcedButton)) == BST_CHECKED)
	{
		wsprintf(cMaritalStatus, TEXT("Divorced")); //cMaritalStatus = {"Divorced"};
	}
	*/

	CreateWindowW(L"static", L"Gender", WS_VISIBLE | WS_CHILD, 50, 330, 55, 20, hwnd,
					NULL, NULL, NULL);

	// Male, Female,other checkbox
	 hMale = CreateWindowEx(0,"Button", "Male", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 240, 330, 60, 20, hwnd,
				NULL, NULL, NULL);
	//CheckDlgButton(hwnd, 1, BST_CHECKED);

	hFemale = CreateWindowEx(0,"Button", "Female", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 460, 330, 75, 20, hwnd,
				NULL, NULL, NULL);

	hOther = CreateWindowEx(0,"Button", "Other", WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 660, 330, 70, 20, hwnd,
				NULL, NULL, NULL);





	CreateWindowW(L"static", L"Occupation", WS_VISIBLE | WS_CHILD, 50, 380, 80, 20, hwnd,
					NULL, NULL, NULL);

	hOccupation = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 380, 500, 25, hwnd,
					NULL, NULL, NULL);
	/*
	CreateWindowW(L"static", L"Religion", WS_VISIBLE | WS_CHILD, 860, 380, 58, 20, hwnd,
					NULL, NULL, NULL);

	hReligion = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 940, 380, 100, 25, hwnd,
					NULL, NULL, NULL);
	*/				
}

//////////////////////////////////////////////////////////////////////////////////////////
//	Function Name : Address
//	Input:			main Handle
//	Output:			void 
//	Description:	Used to display and handle the address form 
//	Author:			Aditya Sakare
////////////////////////////////////////////////////////////////////////////////////////////

void Address(HWND hwnd)
{
	CreateWindowW(L"static", L"Residential Address", WS_VISIBLE | WS_CHILD, 50, 430, 135, 20, hwnd,
					NULL, NULL, NULL);

	hAddress = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 430, 700, 25, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"City / Town", WS_VISIBLE | WS_CHILD, 50, 480, 75, 20, hwnd,
					NULL, NULL, NULL);

	hCity = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 480, 300, 25, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"Pin / Zip Code", WS_VISIBLE | WS_CHILD, 660, 480, 100, 20, hwnd,
					NULL, NULL, NULL);

	hPincode = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 780, 480, 100, 25, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"State", WS_VISIBLE | WS_CHILD, 50, 530, 40, 20, hwnd,
					NULL, NULL, NULL);

	hState = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 530, 300, 25, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"Country", WS_VISIBLE | WS_CHILD, 660, 530, 60, 20, hwnd,
					NULL, NULL, NULL);

	hCountry = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 780, 530, 170, 25, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"Nationality", WS_VISIBLE | WS_CHILD, 50, 580, 80, 20, hwnd,
					NULL, NULL, NULL);

	hNationality = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 580, 250, 25, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"static", L"Mobile No.", WS_VISIBLE | WS_CHILD, 50, 630, 70, 20, hwnd,
					NULL, NULL, NULL);

	hMobile1 = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 630, 300, 25, hwnd,
					NULL, NULL, NULL);

	CreateWindowW(L"button", L"Submit", WS_VISIBLE | WS_CHILD, 660, 630, 70, 30, hwnd, 
		(HMENU)SUBMIT_BUTTON, NULL, NULL);
	/*
	CreateWindowW(L"static", L"Office", WS_VISIBLE | WS_CHILD, 660, 630, 40, 20, hwnd,
					NULL, NULL, NULL);

	hOffice = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 780, 630, 170, 30, hwnd,
					NULL, NULL, NULL);
	
	CreateWindowW(L"static", L"Email", WS_VISIBLE | WS_CHILD, 50, 680, 40, 20, hwnd,
					NULL, NULL, NULL);

	hEmail = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 680, 300, 30, hwnd,
					NULL, NULL, NULL);
	*/

}

//////////////////////////////////////////////////////////////////////////////////////////
//	Function Name : StoreData
//	Input:			main Handle
//	Output:			void 
//	Description:	Used to store the file and perfrom the operations on the file. File saved 
//					as name of patient
//	Author:			Aditya Sakare
////////////////////////////////////////////////////////////////////////////////////////////

void StoreData()
{
	DWORD dwBytesWritten = 0;
	HANDLE hFile;
	char cName[40], cAge[3], cOccupation[20], cAddress[50], cCity[15], cPincode[5], cBirth[10];
	char cState[12], cCountry[12], cNationality[12], cMobile[12]; 
	char FileName[54];
	char FullName[8] = {"Name : "};
	char Day[8] = {"Date : "};
	char Age[7] = {"Age : "};
	char Birth[17] = {"Date of Birth : "};
	char Occupation[14] = {"Occupation : "};
	char Address[11] = {"Address : "};
	char City[8] = {"City : "};
	char Pincode[11] = {"Pincode : "};
	char State[9] = {"State : "};
	char Country[11] = {"Country : "};
	char Nationality[15] = {"Nationality : "};
	char Mobile[10] = {"Mobile : "};
	char Marital[18] = {"Marital Status : "};


	memset(cName, 0, sizeof(cName));
	memset(cAge, 0, sizeof(cAge));
	memset(cBirth, 0, sizeof(cBirth));
	memset(cOccupation, 0, sizeof(cOccupation));
	memset(cAddress, 0, sizeof(cAddress));
	memset(cCity, 0, sizeof(cCity));
	memset(cPincode, 0, sizeof(cPincode));
	memset(cState, 0, sizeof(cState));
	memset(cCountry, 0, sizeof(cCountry));
	memset(cNationality, 0, sizeof(cNationality));
	memset(cMobile, 0, sizeof(cMobile));



	GetWindowText(hName, cName, 40);
	GetWindowText(hAge, cAge, 3);
	GetWindowText(hBirth, cBirth, 10);
	GetWindowText(hOccupation, cOccupation, 20);
	GetWindowText(hAddress, cAddress, 50);
	GetWindowText(hCity, cCity, 15);
	GetWindowText(hPincode, cPincode, 5);
	GetWindowText(hState, cState, 12);
	GetWindowText(hCountry, cCountry, 12);
	GetWindowText(hNationality, cNationality, 12);
	GetWindowText(hMobile1, cMobile, 12);

	//strcat(FullName, cName);

	strcpy(FileName, cName);
	strcat(FileName, ".txt");

	hFile =  CreateFile(FileName,                // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_NEW,             // create new file only
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);                  // no attr. template	

	

	
	WriteFile(hFile, Day, sizeof(Day), &dwBytesWritten, NULL);
	WriteFile(hFile, Date, sizeof(Date), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, FullName, sizeof(FullName), &dwBytesWritten, NULL);
	WriteFile(hFile, cName, sizeof(cName), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, Birth, sizeof(Birth), &dwBytesWritten, NULL);
	WriteFile(hFile, cBirth, sizeof(cBirth), &dwBytesWritten, NULL);


	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, Age, sizeof(Age), &dwBytesWritten, NULL);
	WriteFile(hFile, cAge, sizeof(cAge), &dwBytesWritten, NULL);

//	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

//	WriteFile(hFile, Marital, sizeof(Marital), &dwBytesWritten, NULL);
//	WriteFile(hFile, cMaritalStatus, sizeof(cMaritalStatus), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, Occupation, sizeof(Occupation), &dwBytesWritten, NULL);
	WriteFile(hFile, cOccupation, sizeof(cOccupation), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, Address, sizeof(Address), &dwBytesWritten, NULL);
	WriteFile(hFile, cAddress, sizeof(cAddress), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, City, sizeof(City), &dwBytesWritten, NULL);
	WriteFile(hFile, cCity, sizeof(cCity), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, Pincode, sizeof(Pincode), &dwBytesWritten, NULL);
	WriteFile(hFile, cPincode, sizeof(cPincode), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, State, sizeof(State), &dwBytesWritten, NULL);
	WriteFile(hFile, cState, sizeof(cState), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, Country, sizeof(Country), &dwBytesWritten, NULL);
	WriteFile(hFile, cCountry, sizeof(cCountry), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, Nationality, sizeof(Nationality), &dwBytesWritten, NULL);
	WriteFile(hFile, cNationality, sizeof(cNationality), &dwBytesWritten, NULL);

	SetFilePointer(hFile, 5, NULL, FILE_CURRENT);

	WriteFile(hFile, Mobile, sizeof(Mobile), &dwBytesWritten, NULL);
	WriteFile(hFile, cMobile, sizeof(cMobile), &dwBytesWritten, NULL);


}

//////////////////////////////////////////////////////////////////////////////////////////
//	Function Name : CurrentDate
//	Input:			main Handle
//	Output:			void 
//	Description:	Used to display the current Local date as per the System time
//	Author:			Aditya Sakare
////////////////////////////////////////////////////////////////////////////////////////////

void CurrentDate(LPVOID param)
{
	HDC hdc = NULL;
	SYSTEMTIME st = {0};
    FILETIME ft = {0};

    GetLocalTime(&st);
		
	//code
	hdc = GetDC((HWND)param);
	SetTextColor(hdc, RGB(0, 0, 0));
	wsprintf(Date, TEXT("%02d/%02d/%04d"),st.wDay, st.wMonth, st.wYear);
	TextOut(hdc, 120, 130, Date, (int)_tcslen(Date));
	ReleaseDC((HWND)param, hdc);
}
