#include <stdio.h>

#include <fcntl.h>
#include <io.h>

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"test \n \x095A\x095A\x0928 Hello from C/C++ \n");

	return 0;	

}