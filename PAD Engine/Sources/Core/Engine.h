#include <Core/EngineClock.h>
#include <System/Window/SDLWindow.h>
#include <Graphics/RHI/IRenderer.h>
#include <Graphics/RHI/RenderSettings.h>
#include <System/ECS/Scene.h>
#include <System/Resource/MasterManager.h>
#include <System/Physics/IPhysicContext.h>
#include <Core/Timer.h>

namespace pad	{
namespace core	{

class Engine final
{
public:
	Engine();
	~Engine();

	Engine(const Engine&)  = delete;
	Engine(const Engine&&) = delete;

private:
	gfx::rhi::IRenderer*	mp_renderer;																	/*! The renderer that contains the window and is used to render data. */
	sys::win::SDLWindow*	mp_window;

	sys::ecs::Scene*			m_scene;
	sys::res::MasterManager*	m_resourceManager;
	core::Timer					m_fixedUpdateTimer;

	static sys::phx::IPhysicContext*	m_physicContext;

public:
	void InitSimulation(const gfx::rhi::ContextSettings& _c, const sys::win::WindowSettings& _w);			/*! Initialize the simulation. Reads the config files and initialize the renderer and the window. */
	void StartSimulation();																					/*! Starts the simulation with the parameters given in InitSimulation method. */
	void Simulate();

private:
	void PollEvents();
	void Update();
	void FixedUpdate();
	void LateUpdate();
	void Render();

	void CreateWindow(const sys::win::WindowSettings& _infos);
	void CreateRenderer(const gfx::rhi::ContextSettings& _settings);

	// TODO : Move GenerateMesh to the right place
	void GenerateMesh(gfx::mod::Mesh& _m, const gfx::mod::MeshData& _md);

	void Draw(const gfx::mod::Mesh& _m, const gfx::rhi::RenderSettings& _settings, math::Mat4& _vp);
	void SwapBuffers();
	void ClearBuffers();
	void ResizeContext(const uint32 _w, const uint32 _h);
	void FlushLogs();

public:
	sys::ecs::Scene* const				GetScene() const			{ return m_scene; }
	sys::res::MasterManager* const		GetMasterManager() const	{ return m_resourceManager; }

	static sys::phx::IPhysicContext* const	GetPhysicContext()		{ return m_physicContext; }

public:
	void operator=(const Engine&)	= delete;
	void operator=(const Engine&&)	= delete;
};

} // namespace core
} // namespace pad