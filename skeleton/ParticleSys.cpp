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
		lifeTimeM = 10;
		lifeTimeD = 2;
		break;

	case explosion:
		vM = { 0.0001, 0.0001, 0.0001 };
		vD = { 0.01, 0.01, 0.01 };
		aM = { 0.000001, 0.000001, 0.000001 };
		aD = { 0.00001, 0.00001, 0.00001 };
		pM = { 0.0, 0.0, 0.0 };
		pD = { 1.0, 1.0, 1.0 };
		lifeTimeM = 5;
		lifeTimeD = 2;
		break;
	default:
		break;
	}
	generate(100);
}

void ParticleSys::update(double t)
{
	for (std::list<Particle*>::iterator it = myPops.begin(); it != myPops.end(); ++it) {
		(*it)->integrate(t);
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
		float vN_x = distributionVx(generator);
		float vN_y = distributionVy(generator);
		float vN_z = distributionVz(generator);
		float aN_x = distributionAx(generator);
		float aN_y = distributionAy(generator);
		float aN_z = distributionAz(generator);
		float pN_x = distributionPx(generator);
		float pN_y = distributionPy(generator);
		float pN_z = distributionPz(generator);
		float lifeTimeN = distributionLT(generator);
		
		myPops.push_back(new Particle({ pN_x, pN_y, pN_z }, {vN_x, vN_y, vN_z}, { aN_x, aN_y, aN_z }, 0.01, 1, lifeTimeN));
	}
}
