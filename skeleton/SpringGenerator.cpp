#include "SpringGenerator.h"

void SpringGenerator::update(Particle* pop, double t)
{
	Vector3 relative_pos_vector = _anchor->getPos() - pop->getPos();
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _l0;
	Vector3 f = relative_pos_vector * delta_x * _k;
	pop->addForce(f);
}
