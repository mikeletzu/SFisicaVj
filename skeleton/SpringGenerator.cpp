#include "SpringGenerator.h"

void SpringGenerator::update(Particle* pop, double t)
{
	Vector3 f = -_k * (pop->getPos() - anchor->getPos() - _l0);
}

void SpringGenerator::initL0(Vector3 popPos)
{
	Vector3 diff = popPos - anchor->getPos();
}
