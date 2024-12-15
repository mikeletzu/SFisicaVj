#include "ForceGenerator.h"
#include "Particle.h"
#include "RigidDinBody.h"

void ForceGenerator::update(Particle* pop, double t)
{
	pop->addForce(_f);
}

void ForceGenerator::update(RigidDinBody* pop, double t)
{
	pop->addForce(_f);
}
