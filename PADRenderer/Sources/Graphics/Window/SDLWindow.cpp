#include <PCH.h>
#include <Graphics/Window/SDLWindow.h>

namespace pad	{
namespace gfx	{
namespace win	{

SDLWindow::SDLWindow()
{

}

SDLWindow::~SDLWindow()
{
	if (mp_event)
		delete mp_event;

	SDL_DestroyWindow(mp_window);
	SDL_GL_DeleteContext(mp_context);
	SDL_Quit();
}

void SDLWindow::Init(const WindowSettings& _infos)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_FATAL_S("Error! Could not init SDL.\n");
		return;
	}

	mp_window = SDL_CreateWindow(_infos.title.c_str(), 
		_infos.position.x,
		_infos.position.y,
		_infos.size.x, 
		_infos.size.y, 
		SDL_WINDOW_OPENGL | 
		SDL_WINDOW_RESIZABLE | 
		(_infos.isFullscreen ? SDL_WINDOW_FULLSCREEN : 0x00));

	m_isOpen = true;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

	mp_context = SDL_GL_CreateContext(mp_window);
	SDL_GL_MakeCurrent(mp_window, mp_context);

	mp_event = new SDL_Event();
}

void SDLWindow::Resize(const math::Vec2<unsigned short>& _size)
{
	if(mp_window)
		SDL_SetWindowSize(mp_window, _size.x, _size.y);
}

void SDLWindow::ReloadSettings(const WindowSettings& _infos)
{

}

void SDLWindow::PollEvents()
{
	SDL_Event* events = static_cast<SDL_Event*>(mp_event);
	while (SDL_PollEvent(events))
	{
		if (events->type == SDL_QUIT)
			m_isOpen = false;
		else if (events->type == SDL_WINDOWEVENT_RESIZED)
			m_resizeCallback(events->window.data1, events->window.data2);
	}
}

void SDLWindow::SetResizeCallback(const std::function<void(const unsigned int, const unsigned int)>& _func)
{
	m_resizeCallback = _func;
}

void SDLWindow::SwapBuffer()
{
	SDL_GL_SwapWindow(mp_window);
}

const math::Vec2i SDLWindow::GetPosition() const
{ 
	math::Vec2i v;  
	SDL_GetWindowPosition(mp_window, &v.x, &v.y); 
	return v; 
}

const math::Vec2i SDLWindow::GetSize() const
{
	math::Vec2i v;  
	SDL_GetWindowSize(mp_window, &v.x, &v.y); 
	return v; 
}

} // namespace win
} // namespace gfx
} // namespace pad