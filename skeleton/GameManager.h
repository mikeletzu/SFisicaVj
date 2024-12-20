#pragma once
#include "Carrito.h"
#include "ParticleShape.h"
#include "ParticleSys.h"
#include "RigidBodySys.h"

using namespace physx;

enum Mov
{
	front, left, right, back
};

class GameManager
{
public:
	GameManager(physx::PxScene* scene, physx::PxPhysics* phys) : _gScene(scene), _gPhysics(phys) {};
	void update(double t);
	void initGame();
	void moveProta(Mov m);

private:
	RigidDinBody* _prota = nullptr;
	RigidBodySys* _inputSys = nullptr;
	ParticleSys* _camFollowSys = nullptr;
	Particle* _camPop = nullptr;
	ParticleSys* _snowSys = nullptr;
	ParticleSys* _trailSys = nullptr;
	ParticleSys* _goalSys = nullptr;


	physx::PxScene* _gScene;
	physx::PxPhysics* _gPhysics;

	float protaVel = 20.0;

	void createSuelo();
	void createBorders();

};

