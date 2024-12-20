#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "core.hpp"
#include <iostream>

class RigidDinBody
{
public:
	RigidDinBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, 
		float lifetime = 10, float Density = 0.15, bool isBox = true, Vector3 boxSize = Vector3{ 1,1,1 }, float Dam = 0.998f, physx::PxMaterial* mat = NULL);
	~RigidDinBody();
	inline void addForce(Vector3 f) { _body->addForce(f); };
	inline void addTorque(Vector3 t) { _body->addTorque(t, physx::PxForceMode::eIMPULSE); };
	inline void clearForce() { _body->clearForce(); };
	Vector3 getPos() { return _body->getGlobalPose().p; };
	Vector3 getVel() { return _body->getLinearVelocity(); };
	float getMass() { return _body->getMass(); };

private:
	RenderItem* _renderItem;
	physx::PxRigidDynamic* _body;
	physx::PxScene* _gScene;
	physx::PxPhysics* _gPhysics;
	Vector3 _size;
	float _density;
};