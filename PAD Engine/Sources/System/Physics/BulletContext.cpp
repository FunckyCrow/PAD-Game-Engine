#include <System/Physics/BulletContext.h>
#include <Core/EngineClock.h>

namespace pad	{
namespace sys	{
namespace phx	{

BulletContext::BulletContext()
{	
	// TO DO : Physic Settings
	collisionConfiguration	= new btDefaultCollisionConfiguration();
	dispatcher				= new btCollisionDispatcher(collisionConfiguration);
	broadphaseInterface		= new btDbvtBroadphase();
	solver					= new btSequentialImpulseConstraintSolver();
	dynamicsWorld			= new btDiscreteDynamicsWorld(	dispatcher,
															broadphaseInterface,
															solver,
															collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.81, 0));
}

BulletContext::~BulletContext()
{
}

void BulletContext::Init()
{
}

void BulletContext::Update()
{
	dynamicsWorld->stepSimulation(0.016f);
}

void BulletContext::Clean()
{
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphaseInterface;
	delete solver;
	delete dynamicsWorld;
}

void BulletContext::AddRigidBody(ecs::RigidBody* const _rigidBody)
{
	dynamicsWorld->addRigidBody(_rigidBody->GetBTRigidBody());
}

void BulletContext::AddCollider(ecs::ACollider* const _collider)
{
	dynamicsWorld->addCollisionObject(_collider->GetBTCollider());
}

void BulletContext::RemoveCollider(ecs::ACollider* const _collider)
{
	dynamicsWorld->removeCollisionObject(_collider->GetBTCollider());
}

void BulletContext::RemoveRigidBody(ecs::RigidBody* const _rigidBody)
{
	dynamicsWorld->removeRigidBody(_rigidBody->GetBTRigidBody());
}

} // namespace phx
} // namespace sys
} // namespace pad