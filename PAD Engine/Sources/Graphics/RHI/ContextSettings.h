#pragma once
#include <Common.h>
#include <Math/Vector4.h>
#include <Math/Vector2.h>

namespace pad	{
namespace gfx	{
namespace rhi	{

enum class E_BUFFER_TYPE : int8
{
	NONE			= 0x00,
	DEPTH_BUFFER	= 0x01,
	STENCIL_BUFFER	= 0x02,
	ALL				= DEPTH_BUFFER | STENCIL_BUFFER
};

using BufferType		= E_BUFFER_TYPE;
using TypeBufferType	= std::underlying_type_t<BufferType>;

E_BUFFER_TYPE  operator| (const E_BUFFER_TYPE& left, const E_BUFFER_TYPE& right);
E_BUFFER_TYPE& operator|=(E_BUFFER_TYPE& left, const E_BUFFER_TYPE& right);
E_BUFFER_TYPE  operator& (const E_BUFFER_TYPE& left, const E_BUFFER_TYPE& right);
E_BUFFER_TYPE& operator&=(E_BUFFER_TYPE& left, const E_BUFFER_TYPE& right);

struct ContextSettings final
{
	ContextSettings() :
		viewportSize(0, 0),
		clearColor(0.f, 0.f, 0.f, 1.f),
		frameBufferCount(0),
		enabledBuffers(E_BUFFER_TYPE::ALL),
		areTrianglesCounterClockwise(true)
	{

	}

	math::Vec2i viewportSize;
	math::Vec4f clearColor;
	uint16		frameBufferCount;
	BufferType	enabledBuffers;
	bool		areTrianglesCounterClockwise;
};

} // namespace rhi
} // namesapce gfx
} // namesapce pad