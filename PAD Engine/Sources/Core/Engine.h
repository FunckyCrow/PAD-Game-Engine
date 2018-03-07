#include <System/SDLWindow.h>
#include <Graphics/Renderer.h>

namespace pad
{
namespace core
{

class Engine final
{
public:
	Engine();
	~Engine();

	Engine(const Engine&)  = delete;
	Engine(const Engine&&) = delete;

private:
	gfx::Renderer	m_renderer;																		/*! The renderer that contains the window and is used to render data. */
	sys::SDLWindow* mp_window;

public:
	void InitSimulation();																			/*! Initialize the simulation. Reads the config files and initialize the renderer and the window. */
	void StartSimulation();																			/*! Starts the simulation with the parameters given in InitSimulation method. */
	void PollEvents();
	void Update(const float32 _deltaTime);
	void FixedUpdate(const float32 _deltaTime);
	void Render();

private:
	void CreateWindow(const sys::WindowSettings& _infos, const sys::E_WINDOW_TYPE _windowType);
	void CreateRenderer(const gfx::RenderSettings& settings);

public:
	void operator=(const Engine&) = delete;
	void operator=(const Engine&&) = delete;
};

} // namespace core
} // namespace pad