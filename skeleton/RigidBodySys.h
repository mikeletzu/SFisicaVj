#pragma once
#include "Zone.h"
#include "RBForceRegistry.h"
#include "RigidDinBody.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "WhirlGenerator.h"
#include <list>

class RigidBodySys
{
	public:
		RigidBodySys(physx::PxScene* scene, physx::PxPhysics* phys);
		void update(double t);
		void generate(int amount);
		bool eraseCheck(RigidDinBody* rb);
		void addBody(RigidDinBody* rb);
		void addTimedForce(ForceGenerator* fg, int timer);

	private:
		Zone* _zone;
		std::list<RigidDinBody*> myBodies;
		RBForceRegistry myForceReg;
		physx::PxScene* _gScene;
		physx::PxPhysics* _gPhysics;
		std::vector<int> timers;

		bool isOutZone(Vector3 p);

		void generateRBSDemo();
};

