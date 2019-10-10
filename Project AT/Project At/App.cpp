#include "App.h"

App::App()
	:
	wnd(800, 600, "Game Window")
{}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	//const float c = sin(timer.Peek()) / 2.0f + 0.5f; // Time Dependant Sin Wave,  
	wnd.Gfx().ClearBuffer(0, 0, 0.);  //Ranges from White to blue ( R,  G, B);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}