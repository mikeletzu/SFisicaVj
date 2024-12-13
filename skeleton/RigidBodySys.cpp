#include "RigidBodySys.h"

RigidBodySys::RigidBodySys(physx::PxScene* scene, physx::PxPhysics* phys):
	_gScene(scene), _gPhysics(phys)
{
	_zone = new Zone({ -300,-300,-300 }, { 200,200,200 });
	generateRBSDemo();
}

void RigidBodySys::update(double t)
{
	for (auto it = myBodies.begin(); it != myBodies.end(); ++it) {
		;
	}


}

void RigidBodySys::generateRBSDemo()
{
	//P5.2 TO DO
	RigidDinBody* rdb = new RigidDinBody(_gScene, _gPhysics, Vector4(1.0, 1.0, 0.0, 1.0), physx::PxTransform({0,40,0}), Vector3(0.0, 1.0, 0.0), Vector3(1.0, 1.0, 0.0), 600, 0.3, true, Vector3(3.0, 3.0, 3.0), 1.0);
	myBodies.push_back(rdb);
}
