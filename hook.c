#include <windows.h>
#include<stdio.h>

void SendString(HWND h, char *text)
{
 char buf[256];
 int flag = 1;
 
 while(flag == 1)
 {
  printf("Enter string for sending to notepad:-\n");
  flushall();
  gets(buf);

  for(int i = 0; buf[i] != '\0'; i++)
   PostMessage(h, WM_CHAR, buf[i], 0);

  printf("Do you want send more yes=1 / No=0 :-");
  scanf("%d",&flag);
 }  
}

int main(int argc, char* argv[])
{
 HWND hWnd;
 TCHAR text[] = TEXT("it works!");

 ShellExecute(NULL, "open", "c:/windows/notepad.exe", NULL, NULL, SW_SHOWNORMAL);
 Sleep(100);

 HWND hNotepadWnd = FindWindow(NULL,  "Untitled - Notepad");
 if(hNotepadWnd == NULL)
 {
  printf("Fail FindWindow\n");
  return 1;
 }
 SendMessage(hNotepadWnd, WM_SETTEXT, 0, (LPARAM)text);

 hWnd = FindWindowEx(hNotepadWnd,NULL,"Edit",NULL);
 if(hWnd == NULL)
 {
  printf("Fail FindWindowEx\n");
  return 1;
 }

    SendString(hWnd, "Hello World line 1\n");

 return 0;
}

