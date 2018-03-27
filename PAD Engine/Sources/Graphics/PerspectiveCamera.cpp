#include <Graphics/PerspectiveCamera.h>
#include <Math/Vector3.h>

namespace pad	{
namespace gfx	{

PerspectiveCamera::PerspectiveCamera()
{
}
PerspectiveCamera::~PerspectiveCamera()
{
}
const math::Mat4& PerspectiveCamera::Perspective(float v, float r, float n, float f) //v = FOV, r = aspectRatio, n = near, f = far
{
	_projectionMatrix = math::Mat4(
	  n/r,				0,				0,				0,
		0,			  n/v,				0,				0,
		0,				0,	 -(f+n)/(f-n), -2*(f*n)/(f-n),
		0,				0,			   -1,				0);

	return _projectionMatrix;
}

const math::Mat4& PerspectiveCamera::LookAt(const math::Vec3f& eye, const math::Vec3f& at, const math::Vec3f& up)
{
	math::Vec3f h(at - eye); 
	h.Normalize();
	
	math::Vec3f f = math::CrossProduct(up, h).Normalized();
	
	math::Vec3f g = math::CrossProduct(h, f); 	

	float fe = -math::DotProduct(f, eye);
	float ge = -math::DotProduct(g, eye);
	float he = -math::DotProduct(h, eye);

	_viewMatrix = math::Mat4(	f.x, f.y, f.z, fe,
								g.x, g.y, g.z, ge,
								h.x, h.y, h.z, he,
								0.f, 0.f, 0.f, 1);
	return _viewMatrix;
}

} // namespace gfx
} // namespace pad
