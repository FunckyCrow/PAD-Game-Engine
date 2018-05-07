#pragma once
#include <Graphics/RHI/AVertexBuffer.h>

namespace pad {
namespace gfx {
namespace gl  {

class GLVertexElementBuffer final : public rhi::AVertexBuffer
{
public:
	GLVertexElementBuffer();
	virtual ~GLVertexElementBuffer() = default;

public:
	void GenerateID()	override;
	void Bind()			override;
	void Unbind()		override;
	void BindData(uint32* const _data, const uint32 _dataSize) override;
	void BindData(float* const _data, const uint32 _dataSize, const int32 _vertexElementCount, const uint8 _location) override {}
};

} // namespace gl
} // namespace gfx
} // namespace pad