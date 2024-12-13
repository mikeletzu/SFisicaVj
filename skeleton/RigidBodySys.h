#pragma once
#include "Zone.h"
#include "PopForceRegistry.h"
#include "RigidDinBody.h"
#include "GravityGenerator.h"

class RigidBodySys
{
	public:
		RigidBodySys(physx::PxScene* scene, physx::PxPhysics* phys);
		void update(double t);
		void generate(int amount);
		bool eraseCheck(RigidDinBody* rb);

	private:
		Zone* _zone;
		std::list<RigidDinBody*> myBodies;
		PopForceRegistry myForceReg;
		physx::PxScene* _gScene;
		physx::PxPhysics* _gPhysics;

		bool isOutZone(Vector3 p);

		void generateRBSDemo();
};

