#include "GravityGenerator.h"
#include "Particle.h"

void GravityGenerator::update(Particle* pop, double t)
{
	std::cout << "Gravity: " << (_f * pop->getMass()).y << std::endl;
	pop->addForce(_f * pop->getMass());
}
