#include "BuoyancyForceGenerator.h"
#include "ParticleShape.h"


BuoyancyForceGenerator::BuoyancyForceGenerator(float d, Vector3 pos) : ForceGenerator({0.0, 0.0, 0.0}, true)
{
	_liquid_particle = new ParticleShape(pos, Vector3(0, 0, 0), Vector3(0, 0, 0), 1, 800000, 6000, true, Vector4(0.4, 0.0, 0.8, 0.2), Vector3(20, 2, 20));
}

void BuoyancyForceGenerator::updateForce(Particle* pop, double t)
{
	float h = pop->getPos().y;
	float h0 = _liquid_particle->getPos().y;
	float _height = static_cast<ParticleShape*>(pop)->getHeight(); //height of the particle
	float v = static_cast<ParticleShape*>(pop)->getVol();

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5)
	{
		immersed = 0.0;
	}
	else if (h0 - h > _height * 0.5)
	{ //totally immersed
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / _height + 0.5;

	}
	f.y = _liquid_density * v * immersed * _gravity;
	pop->addForce(f);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
	delete _liquid_particle;
}
