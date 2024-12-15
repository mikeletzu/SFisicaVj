#include "RigidBodySys.h"

RigidBodySys::RigidBodySys(physx::PxScene* scene, physx::PxPhysics* phys):
	_gScene(scene), _gPhysics(phys)
{
	_zone = new Zone({ -300,-300,-300 }, { 200,200,200 });
	generateRBSDemo();
}

void RigidBodySys::update(double t)
{
	for (auto it = myForceReg.begin(); it != myForceReg.end(); ++it) {
		it->second->update(it->first, t);
	}
}

void RigidBodySys::generateRBSDemo()
{
	//P5.2 TO DO
	physx::PxMaterial* mMat1;
	mMat1 = _gPhysics->createMaterial(0.5f, 0.5f, 0.1f); // static friction, dynamic friction, restitution
	RigidDinBody* rdb1 = new RigidDinBody(_gScene, _gPhysics, Vector4(1.0, 1.0, 0.3, 1.0), physx::PxTransform({0,60,0}), Vector3(0.0, 0.0, 0.0), Vector3(1.0, 0.8, 0.0), 600, 2.5, true, Vector3(3.0, 3.0, 2.8), 1.0, mMat1);
	myBodies.push_back(rdb1);
	physx::PxMaterial* mMat2;
	mMat2 = _gPhysics->createMaterial(0.2f, 0.2f, 0.05f); // static friction, dynamic friction, restitution
	RigidDinBody* rdb2 = new RigidDinBody(_gScene, _gPhysics, Vector4(1.0, 1.0, 0.2, 1.0), physx::PxTransform({10,55,-10}), Vector3(0.0, 0.0, 0.0), Vector3(1.0, -1.0, 0.0), 600, 1.6, true, Vector3(2.2, 3.4, 3.0), 1.0, mMat2);
	myBodies.push_back(rdb2);
	physx::PxMaterial* mMat3;
	mMat3 = _gPhysics->createMaterial(0.8f, 0.8f, 0.15f); // static friction, dynamic friction, restitution
	RigidDinBody* rdb3 = new RigidDinBody(_gScene, _gPhysics, Vector4(1.0, 1.0, 0.4, 1.0), physx::PxTransform({0,70,25}), Vector3(0.0, 0.0, 0.0), Vector3(1.0, 0.6, 0.0), 600, 3.0, true, Vector3(3.0, 3.0, 3.6), 1.0, mMat3);
	myBodies.push_back(rdb3);
	RigidDinBody* rdb4 = new RigidDinBody(_gScene, _gPhysics, Vector4(0.93, 1.0, 0.26, 1.0), physx::PxTransform({10,50,12}), Vector3(0.0, 0.0, 0.0), Vector3(0.6, 0.0, 0.3), 600, 2.3, true, Vector3(2.0, 3.0, 3.0), 1.0); //sin mat se queda el por defecto
	myBodies.push_back(rdb4);

	//Obstacles
	physx::PxRigidStatic* obs1 = _gPhysics->createRigidStatic(physx::PxTransform({ 0,40,10 }, physx::PxQuat(0.5, { 0, 0, -1 })));
	physx::PxShape* shape1 = CreateShape(physx::PxBoxGeometry(10.0, 0.5, 20.0));
	obs1->attachShape(*shape1);
	_gScene->addActor(*obs1);
	RenderItem* obs1RI = new RenderItem(shape1, obs1, { 0,0.8,0.8,1 });
	
	physx::PxRigidStatic* obs2 = _gPhysics->createRigidStatic(physx::PxTransform({ 30,30,03 }, physx::PxQuat(0.6, { 0, 0, 1 })));
	physx::PxShape* shape2 = CreateShape(physx::PxBoxGeometry(20.0, 0.5, 20.0));
	physx::PxMaterial* auxMat;
	shape2->getMaterials(&auxMat, 1);
	auxMat->setDynamicFriction(auxMat->getDynamicFriction() * 2.0);
	shape2->setMaterials(&auxMat, 1);
	obs2->attachShape(*shape2);
	_gScene->addActor(*obs2);
	RenderItem* obs2RI = new RenderItem(shape2, obs2, { 0,0.8,0.8,1 });

	//gravedad afecta solo al centro de masas
	GravityGenerator* g = new GravityGenerator({ 0.0, -9.8, 0.0 }, true);
	myForceReg.add(rdb1, g);
	myForceReg.add(rdb2, g);
	myForceReg.add(rdb3, g);
	myForceReg.add(rdb4, g);
	
	//viento afecta generando un torque
	WindGenerator* w = new WindGenerator(0.1, 0.2, { -300,-300,-300 }, { 200,200,200 }, {2.0, 0.0, 0.0});
	myForceReg.add(rdb1, w);
	myForceReg.add(rdb2, w);
	myForceReg.add(rdb3, w);
	myForceReg.add(rdb4, w);
	
}
