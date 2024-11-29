#include "ParticleSys.h"

ParticleSys::ParticleSys(PSType type): _type(type)
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
		_zone = new Zone( {-30,-30,-30}, {200,200,200} );
		interval = -1;
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
		_zone = new Zone( {-30,-30,-30}, {20,20,20} );
		interval = -1;
		break;

	case snow:
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
		break;

	default:
		break;
	}

	generate(200);
}

void ParticleSys::update(double t)
{
	std::list<Particle*>::iterator it = myPops.begin();
	while(it != myPops.end()) {

		for (auto jt = forces.begin(); jt != forces.end(); ++jt) {
			(*jt)->update(*it, t);
		}

		(*it)->integrate(t);

		if (eraseCheck(*it)) {
			delete (*it);
			it = myPops.erase(it);
		}
		else
			++it;
	}
	if (_type == snow) {
		--interval;
		std::cout << interval << std::endl;
	}
	if (!interval) {
		generate(100);
		interval = 200;
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
		
		myPops.push_back(new Particle({ pN_x, pN_y, pN_z }, {vN_x, vN_y, vN_z}, { aN_x, aN_y, aN_z }, 0.01, 1, lifeTimeN));
	}																							//	  damp, m
}

bool ParticleSys::eraseCheck(Particle* p)
{
	if (p->getLT() <= 0.0 || _zone->isOut(p->getPos()))
		return true;

	return false;
}

void ParticleSys::addForce(ForceGenerator* f)
{
	forces.push_back(f);
}
