#pragma once
#include <string>

namespace pad	{
namespace gfx	{
namespace mod	{

struct TextureData
{
	std::string				m_name;
	std::string				m_path;
	int						m_sWrap;
	int						m_tWrap;
	int						m_channel;
};

} // namespace mod
} // namespace gfx
} // namespace pad