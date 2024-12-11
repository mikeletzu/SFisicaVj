#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "core.hpp"

class RigidDinBody
{
public:
	RigidDinBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, float lifetime = 10, float Density = 0.15, bool isBox = true, Vector3 boxSize = Vector3{ 1,1,1 }, float Dam = 0.998f);
	~RigidDinBody();

private:
	RenderItem* _renderItem;
	physx::PxRigidDynamic* _body;
	physx::PxScene* _gScene;
	physx::PxPhysics* _gPhysics;
	Vector3 _size;
	float _density;
};