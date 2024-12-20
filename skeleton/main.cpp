#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
//#include "Text.h"

#include "ParticleShape.h"
#include "RigidDinBody.h"

#include "ParticleSys.h"
#include "RigidBodySys.h"

#include "GravityGenerator.h"
#include "WhirlGenerator.h"

#include "GameManager.h"

std::list<Text*> display_texts;
//std::string display_text = "Practica final (SIM FISICA) - Mikele López de la Hoz";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

RenderItem* xItem = NULL;
RenderItem* yItem = NULL;
RenderItem* zItem = NULL;
RenderItem* originItem = NULL;

PxTransform x, y, z, o;

ParticleSys* mySysA = nullptr;
ParticleSys* mySysB = nullptr;
RigidBodySys* mySysC = nullptr;

RigidDinBody* dinBody = nullptr;

Particle* p = nullptr;

GameManager* gMan = nullptr;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

#pragma region ELEMENTOS DE PRACTICAS COMENTADAS
	/*
	Vector3 xAxis(10, 0, 0), yAxis(0, 10, 0), zAxis(0, 0, 10);
	x = PxTransform(xAxis.x, xAxis.y, xAxis.z);
	y = PxTransform(yAxis.x, yAxis.y, yAxis.z);
	z = PxTransform(zAxis.x, zAxis.y, zAxis.z);
	o = PxTransform(0.0f, 0.0f, 0.0f);
	xItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &x, { 1.0, 0.0, 0.0, 1.0 });
	yItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &y, { 0.0, 1.0, 0.0, 1.0 });
	zItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &z, { 0.0, 0.0, 1.0, 1.0 });
	originItem = new RenderItem(CreateShape(PxSphereGeometry(1.0f)), &o, { 1.0, 1.0, 1.0, 1.0 });
	*/

	//Generar suelo
	/*
	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	Suelo->attachShape(*shape);
	gScene->addActor(*Suelo);
	RenderItem* SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });
	*/

	//mySysA = new ParticleSys(springs);
	//mySysB = new ParticleSys(buoyancy);
	//mySysC = new RigidBodySys(gScene, gPhysics);

#pragma endregion ejes, suelo y creacion de distintos sistemas

	display_texts.push_back(new Text("Practica final (SIM FISICA) - Mikele Lopez de la Hoz", { 133, 300 }, { 1.0, 1.0, 1.0, 0.6 }));
	display_texts.push_back(new Text("press 'b' to start", { 200, 286 }, { 1.0, 1.0, 1.0, 0.6 }));
	gMan = new GameManager(gScene, gPhysics);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

#pragma region ELEMENTOS DE PRACTICAS COMENTADAS
	/*
	if (mySysA != nullptr)
		mySysA->update(t);
	if (mySysB != nullptr)
		mySysB->update(t);
	if (mySysC != nullptr)
		mySysC->update(t);
	if (p != nullptr)
		p->integrate(t);
	*/
#pragma endregion 

	gMan->update(t);
	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	xItem->release();
	yItem->release();
	zItem->release();
	originItem->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'B': //tecla b para empezar
	{
		gMan->initGame();
		gMan->moveProta(front);
		break;
	}
	case 'J':
	{
		gMan->moveProta(left);
		break;
	}
	case 'I':
	{
		gMan->moveProta(front);
		break;
	}
	case 'L':
	{
		gMan->moveProta(right);
		break;
	}
	case 'K':
	{
		gMan->moveProta(back);
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}