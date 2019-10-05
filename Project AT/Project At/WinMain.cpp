#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);    //If Closed Send this Message
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow )
{
	const auto pClassName = "hw3dbutts";
	
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);	// register window class

	// create window instance
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		"Game Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,   //Combineing multple styles For our window
		200, 200, 640, 480,																				
		nullptr, nullptr, hInstance, nullptr
	);
	// show the window
	ShowWindow(hWnd, SW_SHOW);

	MSG msg;   //Message Structure
	bool gResult;
	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);   //It wont Change Messagess 
		DispatchMessage(&msg);	 //Passes Messages to Wnd Proc
	}
	if (gResult == 1)
	{													//This Shows us we had an Error in the Get Message Function

		return -1;
	}

	else
	{
		return msg.wParam;    //Returns the Above message "69"
	}
	
}



