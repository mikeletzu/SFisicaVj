#include "WindGenerator.h"
#include "Particle.h"
#include "RigidDinBody.h"

void WindGenerator::update(Particle* pop, double t)
{
	if (!_zone->isOut(pop->getPos()))
	{
		//compute the drag force
		Vector3 v = pop->getVel();
		Vector3 dif = _f - v;
		Vector3 dragF = (_k1 * dif) + (_k2 * dif.magnitude() * dif);

		//Apply the drag force
		pop->addForce(dragF);
	}
}

void WindGenerator::update(RigidDinBody* pop, double t)
{
	if (!_zone->isOut(pop->getPos()))
	{
		//compute the drag force
		Vector3 v = pop->getVel();
		Vector3 dif = _f - v;
		Vector3 dragF = (_k1 * dif) + (_k2 * dif.magnitude() * dif);
		//Apply the drag force
		if (withTorque) {
			std::cout << "winded ";
			pop->addTorque(dragF);
		}
		pop->addForce(dragF);
	}
}
