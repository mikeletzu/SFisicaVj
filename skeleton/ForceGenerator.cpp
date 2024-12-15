#include "ForceGenerator.h"
#include "Particle.h"

void ForceGenerator::update(Particle* pop, double t)
{
	pop->addForce(_f);
}
