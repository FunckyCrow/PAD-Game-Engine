#pragma once

#include <Math/Vector3.h>

namespace pad	{
namespace core	{

struct Transform final
{
	math::Vec3f		position;
	math::Vec3f		rotation;
	math::Vec3f		scale;
};

} // namespace core
} // namespace pad