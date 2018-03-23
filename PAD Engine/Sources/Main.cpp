#include <iostream>
#include <Core/Engine.h>
#include <Math/Matrix4x4.h>

#undef main

using namespace pad;

void MethodForTestingPurpose()
{
	
}

int main()
{
	MethodForTestingPurpose();

	// Will be read from a config file
	sys::WindowSettings winSettings;

	winSettings.title = "This is a SDL Window.";
	winSettings.position.x = 400u;
	winSettings.position.y = 200u;
	winSettings.size.x = 800u;
	winSettings.size.y = 600u;
	winSettings.isFullscreen = false;
	winSettings.windowType = sys::E_WINDOW_TYPE::ENGINE;

	// Will be read from a config file
	gfx::rhi::RenderSettings renderSettings;

	renderSettings.viewportSize.x = winSettings.size.x;
	renderSettings.viewportSize.y = winSettings.size.y;
	renderSettings.clearColor.r = 0.3f;
	renderSettings.clearColor.g = 0.3f;
	renderSettings.clearColor.b = 0.3f;
	renderSettings.clearColor.a = 1.0f;

	core::Engine engine;
	
	engine.InitSimulation();
	engine.StartSimulation();

	return EXIT_SUCCESS;
}