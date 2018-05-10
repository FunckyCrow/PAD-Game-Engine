#pragma once

#include <PADRenderer/Common.h>
#include <PADRenderer/Graphics/Model/MaterialData.h>
#include <PADRenderer/Graphics/Model/MeshData.h>
#include <PADRenderer/Graphics/Model/TextureData.h>

#include <string>

namespace pad		{
namespace parser	{

void ReadPADMesh(const	std::string&			_inputPath, 
						gfx::mod::MeshData&		_meshData);

void ReadPADMaterial(	const	std::string&			_inputPath,
								gfx::mod::MaterialData&	_materialData,
								gfx::mod::TextureData&	_textureData);

} // namespace parser
} // namespace pad