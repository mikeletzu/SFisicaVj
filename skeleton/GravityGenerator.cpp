#include "GravityGenerator.h"
#include "Particle.h"
#include "RigidDinBody.h"

void GravityGenerator::update(Particle* pop, double t)
{
	pop->addForce(_f * pop->getMass());
}

void GravityGenerator::update(RigidDinBody* pop, double t)
{
	pop->addForce(_f * pop->getMass());
}
