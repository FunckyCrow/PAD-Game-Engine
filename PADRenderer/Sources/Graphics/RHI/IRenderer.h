#pragma once
#include <Common.h>
#include <Graphics/RHI/ATexture.h>
#include <Graphics/Model/MeshData.h>
#include <Graphics/RHI/AVertexArray.h>
#include <Graphics/RHI/AVertexBuffer.h>
#include <Graphics/RHI/RenderSettings.h>
#include <Graphics/RHI/ContextSettings.h>
#include <Graphics/RHI/Shader/AShaderManager.h>
#include <Graphics/RHI/UniformBufferSettings.h>

namespace pad {
namespace gfx {
namespace rhi { 

class IRenderer
{
public:
	virtual ~IRenderer() = default;

protected:
	math::Vec2i				m_viewportSize;
	shad::AShaderManager*	m_shaderManager;

public:
	virtual void Init(const ContextSettings& _settings)								= 0;
	virtual void ClearBuffer()														= 0;
	virtual void ResizeViewport(const uint32 _w, const uint32 _h)					= 0;
	virtual void GenerateTexture(
		ATexture* const _t, 
		const std::string& _path, 
		const rhi::TextureParameters& _param)										= 0;
	virtual void GenerateMesh(
		const mod::MeshData& _md, 
		rhi::AVertexArray* _vao, 
		rhi::AVertexBuffer* _ibo)													= 0;
	virtual void ForwardRendering(
		rhi::AVertexArray* const _vaos, 
		rhi::AVertexBuffer* const _ibos, 
		const rhi::RenderSettings _settings)										= 0;
	virtual void SetCameraUniformBufferData(
		const math::Vec3f& _position,
		const math::Vec3f& _direction,
		const math::Mat4& _vp)														= 0;
	virtual void SetDirectionalLightUniformBufferData(
		const math::Vec3f& _direction,
		const math::Vec3f& _color,
		const float _intensity)														= 0;
	virtual void SetJointsUniformBufferData(
		float* const _joints,
		const uint8 _count)															= 0;
	virtual void CreateUniformBuffer(const UniformBufferSettings& _settings)		= 0;
	virtual bool LoadShaders(
		const std::string& _vPath, 
		const std::string& _fPath,
		const std::string& _name)													= 0;

	inline shad::AShaderManager* const GetShaderManager() { return m_shaderManager; }

protected:
	virtual void InitContext(const rhi::ContextSettings& _settings)					= 0;
	virtual void InitViewPort(const math::Vec2i& _viewportSize)						= 0;
};

} // namespace rhi
} // namespace gfx
} // namespace pad