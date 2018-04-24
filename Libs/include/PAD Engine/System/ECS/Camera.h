#pragma once
#include <Math/Matrix4x4.h>
#include <Utilities/Export.h>
#include <System/ECS/IComponent.h>

namespace pad	{
namespace sys	{
namespace ecs	{

class ENGINE_API Camera : public sys::ecs::IComponent
{
protected:
	math::Mat4 _projectionMatrix;
	math::Mat4 _viewMatrix;

public:
	virtual const math::Mat4& Perspective(float _fov, float _aspectRatio, float _near, float _far)				= 0;
	virtual const math::Mat4& LookAt(const math::Vec3f& eye, const math::Vec3f& center, const math::Vec3f& up)	= 0;

public:
	inline const math::Mat4& GetProjection()	{ return _projectionMatrix; }
	inline const math::Mat4& GetView()			{ return _viewMatrix; }

	const math::Transform& GetTransform() const override { return m_transform; }
	math::Transform& GetTransform()				override { return m_transform; }
};

} // namespace ecs
} // namespace sys
} // namespace pad