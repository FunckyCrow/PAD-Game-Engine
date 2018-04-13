#pragma once

#include <System/Resource/AResourceManager.h>

namespace pad	{
namespace sys	{
namespace res	{

class MeshManager : public AResourceManager
{
public:
	MeshManager();
	~MeshManager();

public:
	sys::res::Resource* const GetResource(const std::string _name) override;
};

} // namespace res
} // namespace sys
} // namespace pad