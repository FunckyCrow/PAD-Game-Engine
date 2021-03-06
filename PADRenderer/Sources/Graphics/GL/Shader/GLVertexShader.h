#pragma once
#include <Graphics/RHI/Shader/AShader.h>

namespace pad	{
namespace gfx	{
namespace gl	{
namespace shad	{

class GLVertexShader final : public rhi::shad::AShader
{
public:
	GLVertexShader();
	virtual ~GLVertexShader();

	GLVertexShader(const GLVertexShader&) = delete;
	GLVertexShader(GLVertexShader&&) = delete;

public:
	bool LoadShader(const char* _path) override;

private:
	bool CompileShader(const char* _shaderCode) override;

public:
	void operator=(const GLVertexShader&) = delete;
	void operator=(GLVertexShader&&) = delete;
};

} // namespace shad
} // namespace gl
} // namespace gfx
} // namespace pad