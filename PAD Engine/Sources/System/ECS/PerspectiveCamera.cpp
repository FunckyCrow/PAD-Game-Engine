#include <EnginePCH.h>
#include <System/ECS/PADObject.h>
#include <System/ECS/PerspectiveCamera.h>
#include <Core/EngineClock.h>

namespace pad	{
namespace sys	{
namespace ecs	{

alias::ComponentID PerspectiveCamera::m_id = INVALID_COMPONENT_ID;

PerspectiveCamera::PerspectiveCamera() :
	m_speed(5.0)
{
	if (m_id != INVALID_COMPONENT_ID)
		m_id = static_cast<alias::ComponentID>(util::GetTypeID<std::remove_const_t<std::remove_reference_t<decltype(*this)>>>());

	Perspective(45, 16.f / 9.f, 0.01f, 1000.f);
	LookAt(math::Vec3f(0, 0, 0), math::Vec3f(0, 0, 0), math::Vec3f::Up());
}

PerspectiveCamera::~PerspectiveCamera()
{

}

void PerspectiveCamera::MoveForward()
{
	m_owner->GetTransform().Move(m_owner->GetTransform().Forward() * m_speed * core::EngineClock::DeltaTime());
}

void PerspectiveCamera::MoveBackward()
{
	m_owner->GetTransform().Move(-m_owner->GetTransform().Forward() * m_speed * core::EngineClock::DeltaTime());
}

void PerspectiveCamera::MoveLeft()
{
	m_owner->GetTransform().Move(m_owner->GetTransform().Right() * m_speed * core::EngineClock::DeltaTime());
}

void PerspectiveCamera::MoveRight()
{
	m_owner->GetTransform().Move(-m_owner->GetTransform().Right() * m_speed * core::EngineClock::DeltaTime());
}

void PerspectiveCamera::MoveUp()
{
	m_owner->GetTransform().Move(m_owner->GetTransform().Up() * m_speed * core::EngineClock::DeltaTime());
}

void PerspectiveCamera::MoveDown()
{
	m_owner->GetTransform().Move(-m_owner->GetTransform().Up() * m_speed * core::EngineClock::DeltaTime());
}

void PerspectiveCamera::Init()
{

}

void PerspectiveCamera::Start()
{
}

void PerspectiveCamera::Update()
{
}

void PerspectiveCamera::FixedUpdate()
{
}

void PerspectiveCamera::LateUpdate()
{
}

const math::Mat4& PerspectiveCamera::Perspective(float v, float r, float n, float f) //v = FOV, r = aspectRatio, n = near, f = far
{
	float fovTan = tan(math::DegreeToRad(v) / 2.f);

	m_fov = v;
	m_aspectRatio = r;
	m_near = n;
	m_far = f;

	_projectionMatrix[0][0] = 1.f / (fovTan * r);
	_projectionMatrix[1][1] = 1.f / fovTan;
	_projectionMatrix[2][2] = -(f + n) / (f - n);
	_projectionMatrix[2][3] = (-2 * f * n) / (f - n);
	_projectionMatrix[3][2] = -1.f;
	_projectionMatrix[3][3] = 0.f;

	return _projectionMatrix;
}

const math::Mat4& PerspectiveCamera::LookAt(const math::Vec3f& eye, const math::Vec3f& at, const math::Vec3f& up)
{
	math::Vec3f h(eye - at); // zc = h
	h.Normalize();

	math::Vec3f f = math::CrossProduct(up, h).Normalized(); // f = xc

	math::Vec3f g = math::CrossProduct(h, f); // g = yc

	float fe = math::DotProduct(f, -eye); // ex = fe
	float ge = math::DotProduct(g, -eye); // ey = ge
	float he = math::DotProduct(h, -eye); // ez = he

	_viewMatrix[0][0] = f.x;
	_viewMatrix[0][1] = f.y;
	_viewMatrix[0][2] = f.z;
	_viewMatrix[0][3] = fe;

	_viewMatrix[1][0] = g.x;
	_viewMatrix[1][1] = g.y;
	_viewMatrix[1][2] = g.z;
	_viewMatrix[1][3] = ge;

	_viewMatrix[2][0] = h.x;
	_viewMatrix[2][1] = h.y;
	_viewMatrix[2][2] = h.z;
	_viewMatrix[2][3] = he;

	return _viewMatrix;
}

void PerspectiveCamera::FirstPersonMouseInput(
	const math::Vec2i& _mousePos,
	const math::Vec2i& _windowSize)
{
	float x = 5 * core::EngineClock::DeltaTime() * float((_windowSize.x / 2.f) - _mousePos.x);
	float y = 5 * core::EngineClock::DeltaTime() * float((_windowSize.y / 2.f) - _mousePos.y);

	x = fmod(x, 360.f);
	y = fmod(y, 360.f);

	float rotX = GetOwner()->GetTransform().Rotation().x - y;
	if (rotX > 89)
		rotX = 89;
	else if (rotX < -89)
		rotX = -89;

	m_owner->GetTransform().SetRotation(math::Vec3f(rotX, m_owner->GetTransform().Rotation().y + x, m_owner->GetTransform().Rotation().z));
	LookAt(m_owner->GetTransform().Position(), m_owner->GetTransform().Position() + m_owner->GetTransform().Forward(), math::Vec3f::Up());
}

json PerspectiveCamera::Serialize()
{
	json j;

	AddDataToJson(j, "_viewMatrix", _viewMatrix.Serialize());
	AddDataToJson(j, "_projectionMatrix", _projectionMatrix.Serialize());

	return j;
}

void PerspectiveCamera::Deserialize(const json& j)
{
	_viewMatrix.Deserialize			(JsonToData<json>(j, "_viewMatrix"));
	_projectionMatrix.Deserialize	(JsonToData<json>(j, "_projectionMatrix"));
}

} // namespace ecs
} // namespace sys
} // namespace pad