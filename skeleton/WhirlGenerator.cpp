#include "WhirlGenerator.h"
#include "Particle.h"
#include "RigidDinBody.h"

void WhirlGenerator::update(Particle* pop, double t)
{
	Vector3 p = pop->getPos();
	if (!_zone->isOut(p))
	{
		//compute the drag force
		Vector3 dragF = _k1 * Vector3((-(p.z - _pos.z)), (-(p.y - _pos.y)), (p.x - _pos.x));

		//std::cout << "whirled ";
		
		//Apply the drag force
		pop->addForce(dragF);
	}
}

void WhirlGenerator::update(RigidDinBody* pop, double t)
{
	Vector3 p = pop->getPos();
	if (!_zone->isOut(p))
	{
		//compute the drag force
		Vector3 dragF = _k1 * Vector3((-(p.z - _pos.z)), (-(p.y - _pos.y)), (p.x - _pos.x));

		//Apply the drag force
		pop->addForce(dragF);
	}
}
