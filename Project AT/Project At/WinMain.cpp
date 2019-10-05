#include "Win.h"
#include <sstream>
#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow )
{
	Window wnd(800, 300, "Our Window"); //Calls Window to set the Name 
	Window wnd2(800, 300, "Our Window2");
	MSG msg;   //Message Structure
	bool gResult;
	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);   
		DispatchMessage(&msg);	 //Passes Messages to Wnd Proc
	}
	if (gResult == 1)
	{					//This Shows us we had an Error in the Get Message Function

		return -1;
	}

	else
	{
		return msg.wParam;    //Returns the Above message "69"
	}
	
}



