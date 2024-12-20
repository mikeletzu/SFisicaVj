#include "HairTieGenerator.h"

void HairTieGenerator::update(Particle* pop, double t)
{
	Vector3 relative_pos_vector = _pAnchor->getPos() - pop->getPos();
	if (relative_pos_vector.magnitude() > _l0) { //solo se aplica la fuerza si esta estirada
		SpringGenerator::update(pop, t);
	}
}
