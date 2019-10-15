#include "App.h"

/* Class Desc  Affectbly App Makes it easier to do stuff to window such as change the window Name Etc Hence why it has Acess to windows and used timer to add background*/
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
	wnd.Gfx().ClearBuffer(0, 0, 0.0F);  //Ranges from White to blue ( R,  G, B);

	wnd.Gfx().Draw(-timer.Peek(), 0.0f, 1.0f); 

	wnd.Gfx().Draw(timer.Peek(),
		wnd.mouse.GetPosX() / 400.0f - 1.0f,  //Used to make the range -1 to 1
		-wnd.mouse.GetPosY() / 300.0f + 1.0f    //Draws wherever mouse is
	);
	wnd.Gfx().EndFrame();
}