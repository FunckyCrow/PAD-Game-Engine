#include <Common.h>
#include <Core/Engine.h>
#include <Core/Timer.h>
#include <Graphics/GL/GLRenderer.h>
#include <Math/Matrix4x4.h>
#include <Logger/SimpleLogger.h>

namespace pad	{
namespace core	{

Engine::Engine()
{

}

Engine::~Engine()
{
	if(mp_window)
		delete mp_window;
	if (mp_renderer)
		delete mp_renderer;
}

void Engine::InitSimulation()
{
	LOG_INIT();
	core::EngineClock::Init();
}

void Engine::StartSimulation()
{
	while (mp_window->IsOpen())
	{
		core::EngineClock::Update();
		PollEvents();

		if (true)
		{
			Update();
			FixedUpdate();
		}

		Render();
	}
}

void Engine::PollEvents()
{
	if(mp_window)
		mp_window->PollEvents();
}

void Engine::Update()
{
	core::Timer::PauseAll();
}

void Engine::FixedUpdate()
{

}

void Engine::Render()
{
	mp_renderer->ClearBuffer();

	gfx::mod::Mesh m;
	mp_renderer->Draw(m);

	mp_window->SwapBuffer();
}

void Engine::CreateWindow(const sys::WindowSettings& _infos)
{
	if (_infos.windowType == sys::E_WINDOW_TYPE::ENGINE)
		mp_window = new sys::SDLWindow();
	else if (_infos.windowType == sys::E_WINDOW_TYPE::EDITOR)
		mp_window = nullptr;

	if(mp_window)
		mp_window->Init(_infos);
}

void Engine::CreateRenderer(const gfx::rhi::ContextSettings& _settings)
{
	mp_renderer = new gfx::gl::GLRenderer();
	mp_renderer->Init(_settings);

	if (mp_window)
	{
		mp_window->SetResizeCallback(
			std::bind(
				&gfx::gl::GLRenderer::ResizeViewport,
				static_cast<gfx::gl::GLRenderer*>(mp_renderer),
				std::placeholders::_1,
				std::placeholders::_2
			)
		);
	}
}

void Engine::ClearBuffer()
{
	if (mp_renderer)
		mp_renderer->ClearBuffer();
}

void Engine::SwapBuffers()
{
	if (mp_window)
		mp_window->SwapBuffer();
}

void Engine::ResizeContext(const uint32 _w, const uint32 _h)
{
	if (mp_renderer)
		mp_renderer->ResizeViewport(_w, _h);
}

void Engine::Draw(const gfx::mod::Mesh& _m, const gfx::rhi::RenderSettings& _settings)
{
	if (mp_renderer)
		mp_renderer->Draw(_m, _settings);
}

void Engine::FlushLogs()
{
	LOG_FLUSH();
}

bool Engine::IsWindowOpen()
{
	if (mp_window)
		return mp_window->IsOpen();
	else
		return false;
}

} // namespace core
} // namespace pad