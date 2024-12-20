#include "ParticleSys.h"

ParticleSys::ParticleSys(PSType type, RigidDinBody* anch): _type(type)
{
	switch (type)
	{
	case fog:
		vM = { 0.00000000000001, 0.00000000000001, 0.00000000000001 };
		vD = { 0.001, 0.001, 0.001 };
		aM = { 0.0, 0.0, 0.0 };
		aD = { 0.000000000001, 0.000000000001, 0.000000000001 };
		pM = { 0.0, 0.0, 0.0 };
		pD = { 10.0, 10.0, 10.0 };
		lifeTimeM = 1000;
		lifeTimeD = 2;
		_zone = new Zone({ -30,-30,-30 }, { 200,200,200 });
		interval = -1;
		generate(200);
		break;

	case explosion:
		vM = { 0.001, 0.001, 0.001 };
		vD = { 0.01, 0.01, 0.01 };
		aM = { 0.0001, 0.0001, 0.0001 };
		aD = { 0.001, 0.001, 0.001 };
		pM = { 0.0, 0.0, 0.0 };
		pD = { 1.0, 1.0, 1.0 };
		lifeTimeM = 500;
		lifeTimeD = 2;
		_zone = new Zone({ -30,-30,-30 }, { 20,20,20 });
		interval = -1;
		generate(200);
		break;

	case snow:
		{
			/*
			vM = { 0.0, -0.05, 0.0 };
			vD = { 0.00000001, 0.01, 0.00000001 };
			aM = { 0.0, -0.0001, 0.0 };
			aD = { 0.00000001, 0.000000001, 0.00000001 };
			pM = { 0.0, 80.0, 0.0 };
			pD = { 10.0, 0.000001, 10.0 };
			lifeTimeM = 5000;
			lifeTimeD = 2;
			_zone = new Zone( {-300,-300,-300}, {200,200,200} );
			interval = 200;
			generate(200);
			*/
			pM = { 0.0, 120.0, 0.0 };
			pD = { 40.0, 30.0, 40.0 };
			lifeTimeM = 300;
			lifeTimeD = 100;
			_zone = new Zone({-100,0,-100}, {100,200,100});
			interval = 100;
			GravityGenerator* g = new GravityGenerator(Vector3(0, -9.8, 0));
			myForces.push_back(g);
			generateGameSnow(100);
		}
		break;
	case springs:
		_zone = new Zone({ -3000,-3000,-3000 }, { 2000,2000,2000 });
		generateSpringAnchDemo();
		generateSpringDuoDemo();
		generateHairTieDemo();
		break;
	case buoyancy:
		_zone = new Zone({ -3000,-3000,-3000 }, { 2000,2000,2000 });
		generateBuoyancyDemo();
		break;
	case camera:
		{
		_zone = new Zone({ -1, -1, -1 }, { -1, -1, -1 });
		ParticleShape* p = new ParticleShape({ 76.0, 5.0, 50.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 2, 600000, false, {0.0, 0.0, 0.0, 0.0}, {0.01, 0.01, 0.01});
		myPops.push_back(p);
		int l0 = (anch->getPos() - p->getPos()).magnitude();
		SpringGenerator* f1 = new SpringGenerator(nullptr, anch, 10.0, l0);
		addForce(f1);
		myForceReg.add(p, f1);
		GravityGenerator* f2 = new GravityGenerator({ 0.0, 5.0, 5.0 }, true);
		addForce(f2);
		myForceReg.add(p, f2);
		}
		break;
	case goal:
		{
		_zone = new Zone({ -1, -1, -1 }, { -1, -1, -1 });
		Particle* anch = new ParticleShape({ 80.0, 1.0, 00.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 1, 600);
		myPops.push_back(anch);
		Particle* p = new Particle({ 80.0, 6.0, 00.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 2, 600);
		myPops.push_back(p);
		int l0 = (anch->getPos() - p->getPos()).magnitude();
		SpringGenerator* f1 = new SpringGenerator(anch, nullptr, 1, l0);
		addForce(f1);
		myForceReg.add(p, f1);
		WhirlGenerator* f3 = new WhirlGenerator( 10.0, 10.0, {1, 1, 1 }, {1, 1, 1}, {1, 1, 1},  {80.0, 0.0, 00.0},  true);
		addForce(f3);
		myForceReg.add(p, f3);
		}
		break;

	case trail:
	{
		toTrail = anch;
		_zone = new Zone({ -1, -1, -1 }, { -1, -1, -1 });
		vM = -anch->getVel();
		vD = { 1, 1, 1 };
		aM = { 10, 10, 10 };
		aD = { 0.1, 0.1, 0.1 };
		pM = anch->getPos();
		pD = {0.2, 0.2, 0.2 };
		lifeTimeM = 5;
		lifeTimeD = 1;
		interval = 10;
		generate(10);
	}
	break;
	default:
		break;
	}
}

void ParticleSys::update(double t)
{
	//std::cout << "ForceRegUpdate: " << std::endl;

	for (auto it = myForceReg.begin(); it != myForceReg.end(); ++it) {
		if(it->second != nullptr)
			it->second->update(it->first, t);		
	}

	//std::cout << "MyPops integrate: " << std::endl;

	std::list<Particle*>::iterator it = myPops.begin();
	int i = 0;
	while(it != myPops.end()) {

		/*
		for (auto jt = myForces.begin(); jt != myForces.end(); ++jt) {
			(*jt)->update(*it, t);
		}
		*/

		//std::cout << "pop" << i << " ";
		(*it)->integrate(t);

		if (eraseCheck(*it)) {
			myForceReg.erase(*it);
			delete (*it);
			it = myPops.erase(it);
		}
		else
			++it;

		++i;
	}
	if (_type == snow || _type == trail) {
		--interval;
		//std::cout << interval << std::endl;
	}
	if (!interval) {
		if (_type == snow) {
			generateGameSnow(100);
			interval = 200;
		}
		else {
			vM = -toTrail->getVel();
			pM = toTrail->getPos();
			interval = 10;
			generate(10);
		}
	}
}

void ParticleSys::generate(int amount)
{
	std::default_random_engine generator;

	std::normal_distribution<double> distributionVx(vM.x, vD.x);
	std::normal_distribution<double> distributionVy(vM.y, vD.y);
	std::normal_distribution<double> distributionVz(vM.z, vD.y);
	std::normal_distribution<double> distributionAx(aM.x, aD.x);
	std::normal_distribution<double> distributionAy(aM.y, aD.y);
	std::normal_distribution<double> distributionAz(aM.z, aD.y);
	std::normal_distribution<double> distributionPx(pM.x, pD.x);
	std::normal_distribution<double> distributionPy(pM.y, pD.y);
	std::normal_distribution<double> distributionPz(pM.z, pD.y);
	std::normal_distribution<double> distributionLT(lifeTimeM, lifeTimeD);

	for (int i = 0; i < amount; ++i) {
		//std::cout << i << std::endl;
		float vN_x = distributionVx(generator);
		//std::cout << "vN_x: " << vN_x << std::endl;
		float vN_y = distributionVy(generator);
		//std::cout << "vN_y: " << vN_y << std::endl;
		float vN_z = distributionVz(generator);
		//std::cout << "vN_z: " << vN_z << std::endl;
		float aN_x = distributionAx(generator);
		//std::cout << "aN_x: " << aN_x << std::endl;
		float aN_y = distributionAy(generator);
		//std::cout << "aN_y: " << aN_y << std::endl;
		float aN_z = distributionAz(generator);
		//std::cout << "aN_z: " << aN_z << std::endl;
		float pN_x = distributionPx(generator);
		//std::cout << "pN_x: " << pN_x << std::endl;
		float pN_y = distributionPy(generator);
		//std::cout << "pN_y: " << pN_y << std::endl;
		float pN_z = distributionPz(generator);
		//std::cout << "pN_z: " << pN_z << std::endl;
		float lifeTimeN = distributionLT(generator);
		//std::cout << "lifeTimeN: " << lifeTimeN << std::endl;
		
		myPops.push_back(new ParticleShape({ pN_x, pN_y, pN_z }, {vN_x, vN_y, vN_z}, { aN_x, aN_y, aN_z }, 0.01, 1, lifeTimeN, false, {1.0, 1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}));
	}																							//	  damp, m
}

void ParticleSys::generateGameSnow(int amount)
{
	std::default_random_engine generator;

	std::normal_distribution<double> distributionMass(0.01, 0.03);
	std::normal_distribution<double> distributionColor(0.6, 0.2);
	std::normal_distribution<double> distributionSize(0.15, 0.05);
	std::normal_distribution<double> distributionPx(pM.x, pD.x);
	std::normal_distribution<double> distributionPy(pM.y, pD.y);
	std::normal_distribution<double> distributionPz(pM.z, pD.z);
	std::normal_distribution<double> distributionLT(lifeTimeM, lifeTimeD);

	for (int i = 0; i < amount; ++i) {

		float colorMult = distributionPx(generator);
		float size = distributionPx(generator);
		float pN_x = distributionPx(generator);
		//std::cout << "pN_x: " << pN_x << std::endl;
		float pN_y = distributionPy(generator);
		//std::cout << "pN_y: " << pN_y << std::endl;
		float pN_z = distributionPz(generator);
		//std::cout << "pN_z: " << pN_z << std::endl;
		float lifeTimeN = distributionLT(generator);
		//std::cout << "lifeTimeN: " << lifeTimeN << std::endl;


		//std::cout << "pop: " << i << std::endl;
		Particle* p = new ParticleShape({ pN_x, pN_y, pN_z }, { 0, 0, 0 }, { 0, 0, 0 }, 0.01, 1, lifeTimeN, false, { 1.0f * colorMult, 1.0f * colorMult, 1.0, 1.0 }, { 0.1, 0.1, 0.1 });
		myPops.push_back(p);
		myForceReg.add(p, *myForces.begin());
	}
}

bool ParticleSys::eraseCheck(Particle* p)
{
	if (p->getLT() <= 0.0 || _zone->isOut(p->getPos())) {
		if (_zone->isOut(p->getPos()))
			//std::cout << "x: " << p->getPos().x << " t saliste d la zona\n";
		return true;
	}

	return false;
}

void ParticleSys::addForce(ForceGenerator* f)
{
	myForces.push_back(f);
}

bool ParticleSys::isOutZone(Vector3 p)
{
	return false;
}

Particle* ParticleSys::getCamPop()
{
	return (*myPops.begin());
}

void ParticleSys::generateSpringAnchDemo() {
	Particle* anch = new ParticleShape({ 0.0, 60.0, 0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 1, 600);
	myPops.push_back(anch);
	Particle* p = new Particle({ 0.0,40.0,0.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 2, 600);
	myPops.push_back(p);
	int l0 = (anch->getPos() - p->getPos()).magnitude();
	SpringGenerator* f1 = new SpringGenerator(anch, nullptr, 1, l0);
	addForce(f1);
	myForceReg.add(p, f1);
	GravityGenerator* f3 = new GravityGenerator({ 0.0, -100.0, 0.0 }, true);
	addForce(f3);
	myForceReg.add(p, f3);
}

void ParticleSys::generateSpringDuoDemo() {
	Particle* p1 = new ParticleShape({ -10.0, 30.0, 10.0 }, { -5.0,5.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 1, 600, true, {0.2, 0.6, 0.9, 0.1});
	myPops.push_back(p1);
	Particle* p2 = new ParticleShape({ 10.0,30.0,-10.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 2, 600, false, { 0.2, 0.6, 0.9, 0.1 });
	myPops.push_back(p2);
	int l0 = (p1->getPos() - p2->getPos()).magnitude();
	SpringGenerator* f1 = new SpringGenerator(p2, nullptr, 0.2, l0);
	addForce(f1);
	myForceReg.add(p1, f1);
	SpringGenerator* f2 = new SpringGenerator(p1, nullptr, 20, l0);
	addForce(f2);
	myForceReg.add(p2, f2);

	Particle* p3 = new ParticleShape({ -10.0, 30.0, -10.0 }, { 5.0,5.0,-5.0 }, { 0.0,0.0,0.0 }, 0.85, 1, 600, true, { 0.9, 0.6, 0.9, 0.1 });
	myPops.push_back(p3);
	Particle* p4 = new ParticleShape({ -10.0,30.0,-10.0 }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 2, 600, false, { 0.9, 0.6, 0.9, 0.1 });
	myPops.push_back(p4);
	l0 = (p3->getPos() - p4->getPos()).magnitude();
	SpringGenerator* f4 = new SpringGenerator(p4, nullptr, 0.6, l0);
	addForce(f4);
	myForceReg.add(p3, f4);
	SpringGenerator* f5 = new SpringGenerator(p3, nullptr, 2, l0);
	addForce(f5);
	myForceReg.add(p4, f5);

	GravityGenerator* f3 = new GravityGenerator({ 0.0, -1000.0, 0.0 }, true);
	addForce(f3);
	myForceReg.add(p2, f3);
	myForceReg.add(p4, f3);
}

void ParticleSys::generateHairTieDemo() {
	ParticleShape* other = new ParticleShape({ float(10.0 + cos(0) * 5.0), float(10.0 + sin(0) * 5.0), -float(10.0 + cos(0) * 5.0) }, { 0.0,-10.0,-10.0 }, { 0.0,0.0,0.0 }, 0.85, 1, 600, false, { 0.0, 0.0, 0.0, 0.1 });
	ParticleShape* aux = other;
	myPops.push_back(other);
	for (int i = 1; i < 10; ++i) {
		float angle = 2 * 3.14159 * i / 11;  // Angle for each point
		ParticleShape* p = new ParticleShape({ float(10.0 + cos(angle)*5.0), float(10.0 + sin(angle) * 5.0), -float(10.0 + cos(angle) * 5.0) }, { 0.0,0.0,0.0 }, { 0.0,0.0,0.0 }, 0.85, 1, 600, false, { float(i/10.0 + 0.3), float(i / 10.0 + 0.3), float(i / 10.0 + 0.3), 0.1 });
		myPops.push_back(p);

		int l0 = (other->getPos() - p->getPos()).magnitude();
		HairTieGenerator* fA = new HairTieGenerator(other, 0.2, l0-1);
		addForce(fA);
		myForceReg.add(p, fA);
		HairTieGenerator* fB = new HairTieGenerator(p, 0.2, l0 - 1);
		addForce(fB);
		myForceReg.add(other, fB);

		other = p;
	}
	int l0 = (other->getPos() - aux->getPos()).magnitude();
	HairTieGenerator* fA = new HairTieGenerator(other, 0.2, l0 - 1);
	addForce(fA);
	myForceReg.add(aux, fA);
	HairTieGenerator* fB = new HairTieGenerator(aux, 0.2, l0 - 1);
	addForce(fB);
	myForceReg.add(other, fB);
}


void ParticleSys::generateBuoyancyDemo()
{
	//CUBO ROJO
	ParticleShape* p1 = new ParticleShape(Vector3(20.0, 1.0, 20.0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.98, 6, 6000, true, Vector4(1.0, 0.0, 0.0, 1.0), Vector3(0.15, 0.3, 0.15));
	myPops.push_back(p1);
	//CUBO VERDE
	ParticleShape* p2 = new ParticleShape(Vector3(30.0, -1.0, 15.0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.98, 2.3, 6000, true, Vector4(0.0, 1.0, 0.0, 1.0), Vector3(0.1, 0.25, 0.1));
	myPops.push_back(p2);
	//CUBO AZUL
	ParticleShape* p3 = new ParticleShape(Vector3(15.0, 0.0, 30.0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.98, 9, 6000, true, Vector4(0.0, 0.0, 1.0, 1.0), Vector3(0.3, 0.5, 0.2));
	myPops.push_back(p3);

	BuoyancyForceGenerator* b = new BuoyancyForceGenerator(1000, Vector3(0, 0, 0));
	myForceReg.add(p1, b);
	myForceReg.add(p2, b);
	myForceReg.add(p3, b);

	
	GravityGenerator* g = new GravityGenerator(Vector3(0, -9.8, 0));
	myForceReg.add(p1, g);
	myForceReg.add(p2, g);
	myForceReg.add(p3, g);	
}