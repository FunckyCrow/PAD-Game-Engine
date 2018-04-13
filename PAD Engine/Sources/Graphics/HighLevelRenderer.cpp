#include <Graphics/HighLevelRenderer.h>
#include <Graphics/GL/GLRenderer.h>
#include <Graphics/Window/SDLWindow.h>
#include <System/ECS/PerspectiveCamera.h>
#include <System/ECS/MeshRenderer.h>

namespace pad	{
namespace gfx	{

HighLevelRenderer::HighLevelRenderer() :
	m_lowLevelRenderer(nullptr),
	m_mainWindow(nullptr)
{

}

HighLevelRenderer::~HighLevelRenderer()
{
	delete m_lowLevelRenderer;
	delete m_mainWindow;
}

void HighLevelRenderer::Initialize(const rhi::ContextSettings& _rSettings, const win::WindowSettings& _wSettings)
{
	switch (_wSettings.windowType)
	{
	case gfx::win::E_WINDOW_TYPE::SDL:
		m_mainWindow = new win::SDLWindow();
		break;
	case gfx::win::E_WINDOW_TYPE::QT:
		break;
	}

	switch (_rSettings.implementationType)
	{
	case rhi::E_RENDERER_IMPLEMENTATION_TYPE::OPENGL:
	default:
		m_lowLevelRenderer = new gl::GLRenderer();
	}

	if (m_mainWindow)
	{
		m_mainWindow->Init(_wSettings);
		m_mainWindow->SetResizeCallback(
			std::bind(
				&gfx::gl::GLRenderer::ResizeViewport,
				static_cast<gfx::gl::GLRenderer*>(m_lowLevelRenderer),
				std::placeholders::_1,
				std::placeholders::_2
			)
		);
	}

	if (m_lowLevelRenderer)
		m_lowLevelRenderer->Init(_rSettings);
}

void HighLevelRenderer::Render(sys::res::MasterManager& _resources)
{
#pragma region Temp Code
	// TODO : Change the temp camera for a main camera in the scene
	sys::ecs::PerspectiveCamera cam;
	cam.Perspective(45.f, 16.f / 9.f, 0.01f, 1000.f);
	cam.LookAt(math::Vec3f(0, 15, -10), math::Vec3f(0, 0, 0), math::Vec3f::Up());

	math::Mat4 vp = cam.GetProjection() * cam.GetView();
#pragma endregion

	ClearBuffers();

	for (const auto& meshRenderer : sys::ecs::MeshRenderer::GetCollection())
	{
		const gfx::mod::Mesh* const currentMesh = _resources.GetMeshManager().GetResource(meshRenderer.GetMeshName());

		if (!currentMesh)
			continue;

		if (m_lowLevelRenderer)
			m_lowLevelRenderer->ForwardRendering(currentMesh->GetVAO(), currentMesh->GetIBO(), meshRenderer.GetSettings(), vp);
	}

	SwapBuffers();
}

void HighLevelRenderer::GenerateMesh(gfx::mod::Mesh& _m, const gfx::mod::MeshData& _md)
{
	if (m_lowLevelRenderer)
		m_lowLevelRenderer->GenerateMesh(_md, _m.GetVAO(), _m.GetIBO());
}

bool HighLevelRenderer::IsWindowOpen()
{
	if (m_mainWindow)
		return m_mainWindow->IsOpen();
	return false;
}

void HighLevelRenderer::PollEvents()
{
	if (m_mainWindow)
		m_mainWindow->PollEvents();
}

void HighLevelRenderer::ClearBuffers()
{
	if(m_lowLevelRenderer)
		m_lowLevelRenderer->ClearBuffer();
}

void HighLevelRenderer::SwapBuffers()
{
	if(m_mainWindow)
		m_mainWindow->SwapBuffer();
}

void HighLevelRenderer::ResizeContext(const uint32 _w, const uint32 _h)
{
	m_lowLevelRenderer->ResizeViewport(_w, _h);
}

} // namespace gfx
} // namespace pad