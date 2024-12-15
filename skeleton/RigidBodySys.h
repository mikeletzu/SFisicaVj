#pragma once
#include "Zone.h"
#include "RBForceRegistry.h"
#include "RigidDinBody.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include <list>

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
		RBForceRegistry myForceReg;
		physx::PxScene* _gScene;
		physx::PxPhysics* _gPhysics;

		bool isOutZone(Vector3 p);

		void generateRBSDemo();
};

