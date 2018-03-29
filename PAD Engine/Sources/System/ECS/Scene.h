#pragma once

#include <vector>
#include <System/ECS/PADObject.h>
#include <Graphics/Camera.h>

namespace pad	{
namespace sys	{
namespace ecs	{

class Scene final
{
#pragma region Constructor / Destructor

public:
	Scene();
	~Scene();

	Scene(const Scene&)		= delete;
	Scene(const Scene&&)	= delete;

#pragma endregion


private:
	PADObject*		m_masterPADObject;
	gfx::Camera*	m_mainCamera;

public:
	void Update();
	void AddPADObject(PADObject* _PADObject);

public:
	inline PADObject* const GetMasterObject() const { return m_masterPADObject; }
};

} // namespace ecs
} // namespace sys
} // namespace pad