#pragma once
#include <Math/MatrixTransform.h>
#include <Math/Vector4.h>

namespace pad	{
namespace math	{
using Mat4 = Matrix4x4;

class Transform final
{
public:
	inline Transform()		= default;
	inline ~Transform()		= default;

private:
	Mat4	localTransform;
	Mat4	globalTransform;
	Vec3f	position;
	Vec3f	rotation;
	Vec3f	scale;
	bool	isDirty;

private:
	inline void ComputeLocalMatrix()
	{
		localTransform = TranslationMatrix(position)
			*	RotationMatrix()
			*	ScaleMatrix();

		isDirty = false;
	}

public:
	inline const Mat4& GetGlobalTransform() const { return globalTransform; }

	inline const Mat4& GetLocalTransform()
	{
		if (isDirty)
			ComputeLocalMatrix();

		return localTransform;
	}

	inline void SetGlobalTransform(const Mat4& _globalTransform)
	{
		globalTransform = _globalTransform;
	}

	inline void SetPosition(const Vec3f& _position)
	{
		position = _position;
		isDirty = true;
	}

	inline void Move(const Vec3f& _movement)
	{
		position += _movement;
		isDirty = true;
	}
	 
	inline void SetRotation(const Vec3f& _rotation)
	{
		rotation = _rotation;
		isDirty = true;
	}
	 
	inline void SetScale(const Vec3f& _scale)
	{
		scale = _scale;
		isDirty = true;
	}

	inline void SetScale(const float _scalar)
	{
		scale = Vec3f(_scalar, _scalar, _scalar);
		isDirty = true;
	}

	inline void ScaleBy(const float _scalar)
	{
		scale *= _scalar;
		isDirty = true;
	}
};

} // namespace math
} // namespace pad
