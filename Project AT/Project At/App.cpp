#include "App.h"
#include "Box.h"
#include "Cylinder.h"
#include "Pyramid.h"
#include "SkinnedBox.h"
#include <memory>
#include <algorithm>
#include "Maths.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "imgui/imgui.h"
#include "SkinnedBox.h"

//namespace dx = DirectX;
//
//GDIPlusManager gdipm;
//
//App::App()
//	:
//	wnd(1280, 720, "The Donkey Fart Box"),
//	light(wnd.Gfx())
//{
//
//	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f));
//}
//
//void App::DoFrame()
//{
//	const auto dt = timer.Mark() * speed_factor;
//	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
//	wnd.Gfx().SetCamera(cam.GetMatrix());
//	light.Bind(wnd.Gfx(), cam.GetMatrix());
//
//	//nano.Draw( wnd.Gfx() );
//	light.Draw(wnd.Gfx());
//
//	while (const auto e = wnd.kbd.ReadKey())
//	{
//		if (!e->IsPress())
//		{
//			continue;
//		}
//
//		switch (e->GetCode())
//		{
//		case VK_ESCAPE:
//			if (wnd.CursorEnabled())
//			{
//				wnd.DisableCursor();
//				wnd.mouse.EnableRaw();
//			}
//			else
//			{
//				wnd.EnableCursor();
//				wnd.mouse.DisableRaw();
//			}
//			break;
//		case VK_F1:
//			//showDemoWindow = true;
//			break;
//		}
//	}
//
//	if (!wnd.CursorEnabled())
//	{
//		if (wnd.kbd.KeyIsPressed('W'))
//		{
//			cam.Translate({ 0.0f,0.0f,dt });
//		}
//		if (wnd.kbd.KeyIsPressed('A'))
//		{
//			cam.Translate({ -dt,0.0f,0.0f });
//		}
//		if (wnd.kbd.KeyIsPressed('S'))
//		{
//			cam.Translate({ 0.0f,0.0f,-dt });
//		}
//		if (wnd.kbd.KeyIsPressed('D'))
//		{
//			cam.Translate({ dt,0.0f,0.0f });
//		}
//		if (wnd.kbd.KeyIsPressed('R'))
//		{
//			cam.Translate({ 0.0f,dt,0.0f });
//		}
//		if (wnd.kbd.KeyIsPressed('F'))
//		{
//			cam.Translate({ 0.0f,-dt,0.0f });
//		}
//	}
//
//	while (const auto delta = wnd.mouse.ReadRawDelta())
//	{
//		if (!wnd.CursorEnabled())
//		{
//			cam.Rotate((float)delta->x, (float)delta->y);
//		}
//	}
//
//	// imgui windows
//	cam.SpawnControlWindow();
//	light.SpawnControlWindow();
//	//nano.ShowWindow();
//
//	// present
//	wnd.Gfx().EndFrame();
//}
//
//
//App::~App()
//{}
//
//
//int App::Go()
//{
//	while (true)
//	{
//		// process all messages pending, but to not block for new messages
//		if (const auto ecode = Window::ProcessMessages())
//		{
//			// if return optional has value, means we're quitting so return exit code
//			return *ecode;
//		}
//		DoFrame();
//	}
//}



namespace dx = DirectX;

GDIPlusManager gdipm;

App::App()
	:
	wnd(800, 600, "My Window"),
	light(wnd.Gfx())
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			const DirectX::XMFLOAT3 mat = {cdist(rng),cdist(rng),cdist(rng) };

			switch (sdist(rng))
			{
			case 0:
				return std::make_unique<Box>(
					gfx, rng, adist, ddist,
					odist, rdist, bdist, mat
					);
			case 1:
				return std::make_unique<Cylinder>(
					gfx, rng, adist, ddist, odist,
					rdist, bdist, tdist
					);
			case 2:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist, odist,
					rdist, tdist
					);

			case 3:
				return std::make_unique<SkinnedBox>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			default:
				assert(false && "impossible drawable option in factory");
				return {};
			}
			/*return std::make_unique<Box>(
				gfx, rng, adist, ddist,
				odist, rdist, bdist, mat
				);*/
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> sdist{ 0,3 }; //This has to  match the cases
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_real_distribution<float> cdist{ 0.0f,1.0f };
		std::uniform_int_distribution<int> tdist{ 3,30 };
	};

	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, Factory{ wnd.Gfx() });

	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());
	light.Bind(wnd.Gfx(), cam.GetMatrix());

	for (auto& d : drawables)
	{
		d->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		d->Draw(wnd.Gfx());
	}

	light.Draw(wnd.Gfx());

	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_F1:
			//showDemoWindow = true;
			break;
		}
	}

	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed('W'))
		{
			cam.Translate({ 0.0f,0.0f,dt });
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			cam.Translate({ -dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			cam.Translate({ 0.0f,0.0f,-dt });
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			cam.Translate({ dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('R'))
		{
			cam.Translate({ 0.0f,dt,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('F'))
		{
			cam.Translate({ 0.0f,-dt,0.0f });
		}

		// imgui window to control simulation speed
		if (ImGui::Begin("Simulation Speed"))
		{
			ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 6.0f, "%.4f", 3.2f);
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Status: %s", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING (hold spacebar to pause)");
		}

		while (const auto delta = wnd.mouse.ReadRawDelta())
		{
			if (!wnd.CursorEnabled())
			{
				cam.Rotate((float)delta->x, (float)delta->y);
			}
		}

		//ImGui::End();
		// imgui windows to control camera and light
		cam.SpawnControlWindow();
		light.SpawnControlWindow();

		// present
		wnd.Gfx().EndFrame();
	}
}

App::~App()
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