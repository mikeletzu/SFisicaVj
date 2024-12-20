#include "GameManager.h"

void GameManager::update(double t)
{
	//if (_camFollowSys != nullptr) {
		//_camFollowSys->update(t);
	//}
	if (_prota != nullptr) {
		if (_prota->getPos() == Vector3(80.0, 1.0, 00.0)) {
		Text* txt = new Text("YOU WON!!", { 200, 286 }, { 1.0, 1.0, 1.0, 1.0 });
		display_texts.push_back(txt);
		}
		_inputSys->update(t);
		GetCamera()->setDir(_prota->getPos());
		GetCamera()->setEye({ _prota->getPos().x*0.8f, 60.0f, _prota->getPos().z + 30.0f });
	}
	else {
		if (display_texts.size() >= 6) {//estamos en la pantalla de juego
			std::cout << "prota a null en juego";
			Text* txt = new Text("GAME OVER\npulse ESC", { 200, 286 }, { 1.0, 1.0, 1.0, 1.0 });
			display_texts.push_back(txt);
		}
	}
	
	if (_snowSys != nullptr) {
		_snowSys->update(t);
	}
	if (_goalSys != nullptr) {
		_goalSys->update(t);
	}
	if (_trailSys != nullptr) {
		_trailSys->update(t);
	}
}

void GameManager::initGame()
{
	GetCamera()->setDir({0.0, 0.0, 0.0});
	GetCamera()->setEye({0.0, 200.0, 20.0});

	createSuelo();
	createBorders();

	_goalSys = new ParticleSys(goal);

	_prota = new RigidDinBody(_gScene, _gPhysics, Vector4(1.0, 1.0, 0.0, 1.0), physx::PxTransform({ 76.0,2.0,50.0 }), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), 9999999, 2.5, true, Vector3(2.0, 0.6, 1.0), 1.0);
	//Camara
	_camFollowSys = new ParticleSys(camera, _prota);
	_camPop = _camFollowSys->getCamPop();

	_inputSys = new RigidBodySys(_gScene, _gPhysics);
	_inputSys->addBody(_prota);

	//al principio de la partida tenemos solo dos txt
	(*display_texts.begin())->setPos({ 20, 20 });
	display_texts.pop_back();
	//Aclaracion de las teclas
	display_texts.push_back(new Text("         _______", { 400.f, 104.f }, { 1.0, 1.0, 1.0, 1.0 }));
	display_texts.push_back(new Text("        |   ^   |", { 400.f, 90.f }, { 1.0, 1.0, 1.0, 1.0 }));
	display_texts.push_back(new Text("        |   I   |", { 400.f, 76.f }, { 1.0, 1.0, 1.0, 1.0 }));
	display_texts.push_back(new Text(" _______|_______|_______", { 400.f, 62.f }, { 1.0, 1.0, 1.0, 1.0 }));
	display_texts.push_back(new Text("|       |       |       |", { 400.f, 48.f }, { 1.0, 1.0, 1.0, 1.0 }));
	display_texts.push_back(new Text("|  < J  |   K   |  L >  |", { 400.f, 34.f }, { 1.0, 1.0, 1.0, 1.0 }));
	display_texts.push_back(new Text("|_______|___v___|_______|", { 400.f, 20.f }, { 1.0, 1.0, 1.0, 1.0 }));

	_snowSys = new ParticleSys(snow);
	_trailSys = new ParticleSys(trail, _prota);

}
void GameManager::moveProta(Mov m)
{
	Vector3 f = { 0.0, 0.0, 0.0 };
	switch (m)
	{
	case front:
		f.z = -protaVel;
		break;
	case left:
		f.x = -protaVel;
		break;
	case right:
		f.x = protaVel;
		break;
	case back:
		f.z = protaVel;
		break;
	default:
		break;
	}
	ForceGenerator* fg = new WindGenerator(0.6, 1.0, { 1,  1,  1 }, { 1,  1,  1 }, f);
	_inputSys->addTimedForce(fg, (rand() % 5) + 1);
}

void GameManager::createSuelo()
{
	float dim = 100.0;

	PxRigidStatic* Suelo = _gPhysics->createRigidStatic(PxTransform({ -3*dim/4, 0, -dim / 4 }));
	PxShape* shape = CreateShape(PxBoxGeometry(dim/4, 1, dim/2));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	RenderItem* SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });
		
	Suelo = _gPhysics->createRigidStatic(PxTransform({ 0,0,-5*dim /8}));
	shape = CreateShape(PxBoxGeometry(dim *0.575f, 1, dim / 8));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });

	Suelo = _gPhysics->createRigidStatic(PxTransform({ 0,0,-3.3f*dim /8}));
	shape = CreateShape(PxBoxGeometry(dim / 14, 1, dim / 10));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });

	Suelo = _gPhysics->createRigidStatic(PxTransform({ 2*dim / 8,0,-3.3f*dim /8}));
	shape = CreateShape(PxBoxGeometry(dim / 11, 1, dim / 10));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });

	Suelo = _gPhysics->createRigidStatic(PxTransform({ 4* dim / 8,0,-3.3f*dim /8}));
	shape = CreateShape(PxBoxGeometry(dim / 14, 1, dim / 10));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });

	Suelo = _gPhysics->createRigidStatic(PxTransform({ 3 * dim / 8,0,-dim/8 }));
	shape = CreateShape(PxBoxGeometry(dim / 2, 1, dim / 4));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });

	Suelo = _gPhysics->createRigidStatic(PxTransform({ -2 * dim / 4, 0, dim / 4 }));
	shape = CreateShape(PxBoxGeometry(dim * 0.2, 1, dim / 2));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });

	Suelo = _gPhysics->createRigidStatic(PxTransform({ 0,0,5 * dim / 8 }));
	shape = CreateShape(PxBoxGeometry(dim / 2, 1, dim / 8));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });

	Suelo = _gPhysics->createRigidStatic(PxTransform({ 3*dim / 4 ,0, dim / 2 }));
	shape = CreateShape(PxBoxGeometry(dim / 4, 1, dim / 4));
	Suelo->attachShape(*shape);
	_gScene->addActor(*Suelo);
	SueloRenderItem = new RenderItem(shape, Suelo, { 0,1,0.3,1 });
}

void GameManager::createBorders()
{

	PxRigidStatic* Border = _gPhysics->createRigidStatic(PxTransform({ -100, 0, 0}));
	PxShape* shape = CreateShape(PxBoxGeometry(2, 2, 100));
	Border->attachShape(*shape);
	_gScene->addActor(*Border);
	RenderItem* SueloRenderItem = new RenderItem(shape, Border, { 0,1,1,1 });

	Border = _gPhysics->createRigidStatic(PxTransform({ 0,0,-100 }));
	shape = CreateShape(PxBoxGeometry(102, 2, 2));
	Border->attachShape(*shape);
	_gScene->addActor(*Border);
	SueloRenderItem = new RenderItem(shape, Border, { 0,1,1,1 });

	Border = _gPhysics->createRigidStatic(PxTransform({ 100,0,0 }));
	shape = CreateShape(PxBoxGeometry(2, 2, 100));
	Border->attachShape(*shape);
	_gScene->addActor(*Border);
	SueloRenderItem = new RenderItem(shape, Border, { 0,1,1,1 });

	Border = _gPhysics->createRigidStatic(PxTransform({ 0,0,100 }));
	shape = CreateShape(PxBoxGeometry(102, 2, 2));
	Border->attachShape(*shape);
	_gScene->addActor(*Border);
	SueloRenderItem = new RenderItem(shape, Border, { 0,1,1,1 });

}
