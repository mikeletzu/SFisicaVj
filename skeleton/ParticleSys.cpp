#include "ParticleSys.h"

ParticleSys::ParticleSys(PSType type)
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
		lifeTimeM = 100;
		lifeTimeD = 2;
		break;

	case explosion:
		vM = { 0.0001, 0.0001, 0.0001 };
		vD = { 0.01, 0.01, 0.01 };
		aM = { 0.000001, 0.000001, 0.000001 };
		aD = { 0.00001, 0.00001, 0.00001 };
		pM = { 0.0, 0.0, 0.0 };
		pD = { 1.0, 1.0, 1.0 };
		lifeTimeM = 500;
		lifeTimeD = 2;
		break;
	default:
		break;
	}

	zone = { {-30,-30,-30}, {20,20,20} };
	generate(100);
}

void ParticleSys::update(double t)
{
	std::list<Particle*>::iterator it = myPops.begin();
	while(it != myPops.end()) {
		(*it)->integrate(t);
		if (eraseCheck(*it)) {
			delete (*it);
			it = myPops.erase(it);
		}
		else
			++it;
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
		std::cout << i << std::endl;
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
		std::cout << "lifeTimeN: " << lifeTimeN << std::endl;
		
		myPops.push_back(new Particle({ pN_x, pN_y, pN_z }, {vN_x, vN_y, vN_z}, { aN_x, aN_y, aN_z }, 0.01, 1, lifeTimeN));
	}
}

bool ParticleSys::eraseCheck(Particle* p)
{
	if (p->getLT() <= 0.0 || isOutZone(p->getPos()))
		return true;

	return false;
}

bool ParticleSys::isOutZone(Vector3 p)
{
	return (p.x < zone.first.x || p.x > zone.second.x || p.y < zone.first.y || p.y > zone.second.y || p.z < zone.first.z || p.z > zone.second.z);
}
