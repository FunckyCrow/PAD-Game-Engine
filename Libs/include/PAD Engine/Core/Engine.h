#include <Core/EngineClock.h>
#include <Graphics/HighLevelRenderer.h>
#include <Graphics/RHI/RenderSettings.h>
#include <Graphics/Model/Mesh.h>
#include <System/ECS/Scene.h>
#include <System/Resource/MasterManager.h>
#include <System/Resource/ResourceManager.h>
#include <System/Physics/IPhysicContext.h>

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
	gfx::HighLevelRenderer		m_highLevelRenderer;

	sys::ecs::Scene*			m_scene;
	sys::res::MasterManager*	m_resourceManager;
	sys::phx::IPhysicContext*	m_physicContext;

public:
	void InitSimulation(const gfx::rhi::ContextSettings& _c, const gfx::win::WindowSettings& _w);			/*! Initialize the simulation. Reads the config files and initialize the renderer and the window. */
	void StartSimulation();																					/*! Starts the simulation with the parameters given in InitSimulation method. */
	void Simulate();

private:
	void PollEvents();
	void Update();
	void FixedUpdate();
	void LateUpdate();
	void Render();

	void ResizeContext(const uint32 _w, const uint32 _h);
	void FlushLogs();

public:
	sys::ecs::Scene* const				GetScene() const			{ return m_scene; }
	sys::res::MasterManager* const		GetResourceManager() const	{ return m_resourceManager; }

public:
	void operator=(const Engine&)	= delete;
	void operator=(const Engine&&)	= delete;
};

} // namespace core
} // namespace pad