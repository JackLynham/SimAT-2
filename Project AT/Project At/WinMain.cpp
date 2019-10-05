#include "Win.h"
#include <sstream>
#include "Window.h"
#include "ChiliException.h"

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow )
{
	try
	{


		Window wnd(800, 300, "Our Window"); //Calls Window to set the Name 

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
		
			return msg.wParam;    

	}
	catch (const ChiliException & e)
		{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK |   //Shows up Message box with Exception
			MB_ICONEXCLAMATION);
		}
	catch (const std::exception & e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;

}



