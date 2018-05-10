#include <EnginePCH.h>
#include <Core/EngineDLL.h>
#include <Core/Engine.h>
#include <Shlwapi.h>
#include <AssetParser/AssetReader.h>
#include <stb_image/stb_image.h>
#include <Graphics/GL/GLTexture.h>
#
#include <Math/Transform.h>

#pragma comment(lib,"shlwapi.lib")

namespace pad	{

core::Engine* g_engine = nullptr;

void CreateEngine()
{
	if (!g_engine)
		g_engine = new core::Engine();
	else
		LOG_WARNING_S("The engine was already created.\n");
}

void DestroyEngine()
{
	if (g_engine)
		delete g_engine;
//	else
//		LOG_ERROR_S("Error! Call CreateEngine() first.\n");
}

void InitEngine(const gfx::rhi::ContextSettings& _c, const gfx::win::WindowSettings& _w)
{
	if (g_engine)
		g_engine->InitSimulation(_c, _w);
//	else
//		LOG_ERROR_S("Error! Call CreateEngine() first.\n");
}

void StartSimulation()
{
	if (g_engine)
		g_engine->StartSimulation();
//	else
//		LOG_ERROR_S("Error! Call CreateEngine() first.\n");
}

void Simulate()
{
	if (g_engine)
		g_engine->Simulate();
//	else
//		LOG_ERROR_S("Error! Call CreateEngine() first.\n");
}

void AddPADObject(sys::ecs::PADObject* const _padObject)
{
	if(g_engine && g_engine->GetScene())
		g_engine->GetScene()->AddPADObject(_padObject);
}

void RemovePADObject(sys::ecs::PADObject* const _padObject)
{
	if(_padObject->GetParent())
		_padObject->GetParent()->RemoveChild(_padObject);
}

void MoveMainCamera(math::Vec3f& _translation)
{
	if (g_engine && g_engine->GetScene()) 
		g_engine->GetScene()->GetMainCamera().GetTransform().Move(_translation);
}

void RotateMainCamera(math::Vec3f& _rotation)
{
	if (g_engine && g_engine->GetScene())
		g_engine->GetScene()->GetMainCamera().GetTransform().SetRotation(_rotation);
}

void SetMainCameraTarget(const math::Vec3f& _targetPosition)
{
	if (g_engine && g_engine->GetScene())
	{
		sys::ecs::PerspectiveCamera& cam = g_engine->GetScene()->GetMainCamera();
		cam.LookAt(cam.GetTransform().Position(), _targetPosition, math::Vec3f::Up());
	}
}

void LoadResourceFile(const std::string& _filePath, const std::string& _outputPath)
{
	if (g_engine)
	{
		std::string ext = PathFindExtension(_filePath.c_str());
		if (ext == ".PADMesh")
			LoadMeshFile(_filePath);
		else if (ext == ".PADMaterial")
			LoadMaterialFile(_filePath);
	}
}

ENGINE_API void LoadMeshFile(const std::string& _filePath)
{
	std::string	name		= PathFindFileName(_filePath.c_str());
	size_t		extIndex	= name.find_last_of(".");
	name					= name.substr(0, extIndex);

	gfx::mod::MeshData	meshData;
	gfx::mod::Mesh		mesh;

	parser::ReadPADMesh(_filePath, meshData);

	g_engine->GetRenderer().GenerateMesh(mesh, meshData);
	g_engine->GetResourceManager()->GetMeshManager().AddResource(name, mesh);
}

ENGINE_API void LoadMaterialFile(const std::string& _filePath)
{
	gfx::mod::MaterialData	materialData;
	gfx::mod::Material		material;
	gfx::mod::TextureData	textureData;
	gfx::gl::GLTexture*		texture = new gfx::gl::GLTexture();

	parser::ReadPADMaterial(_filePath, materialData, textureData);

	material.SetAmbient(materialData.m_ambient);
	material.SetDiffuse(materialData.m_diffuse);
	material.SetSpecular(materialData.m_specular);
	material.SetShiness(materialData.m_shiness);
	material.SetName(materialData.m_name);

	gfx::rhi::TextureParameters param;
	param.sWrap = gfx::rhi::E_WRAP_TYPE(textureData.m_sWrap);
	param.tWrap = gfx::rhi::E_WRAP_TYPE(textureData.m_tWrap);
	texture->SetName(textureData.m_name);
	g_engine->GetRenderer().GenerateTexture(texture, textureData.m_path, param);

	material.SetAlbedoMapName(textureData.m_name);

	g_engine->GetResourceManager()->GetMaterialManager().AddResource(material.GetName(), material);
	g_engine->GetResourceManager()->GetTextureManager().AddResource(texture->GetName(), texture);
}

} // namespace pad