#pragma once
#include <Math/Transform.h>
#include <System/ECS/Camera.h>

namespace pad	{
namespace sys	{
namespace ecs	{

class ENGINE_API PerspectiveCamera final : public Camera
{
public:
	PerspectiveCamera();
	~PerspectiveCamera();

public:
	void Init()						override;
	void Start()					override;
	void Update()					override;
	void FixedUpdate()				override;
	void LateUpdate()				override;

	json Serialize()				override;
	void Deserialize(const json& j)	override;

public:
	const math::Mat4& Perspective(float _fov, float _aspectRatio, float _near, float _far) override;
	const math::Mat4& LookAt(const math::Vec3f& _eyePos, const math::Vec3f& _target, const math::Vec3f& _up) override;
	void MoveForward(const float32 _speed);
	void MoveBackward(const float32 _speed);

	const alias::ComponentID GetType() const override
	{
		return m_id;
	}

private:
	static alias::ComponentID m_id;
};

} // namespace ecs
} // namespace sys
} // namespace pad