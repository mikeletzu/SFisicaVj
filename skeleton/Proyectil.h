#pragma once
#include "Particle.h"
class Proyectil :
    public Particle
{
public:
	Proyectil(Vector3 Pos, Vector3 Vel, Vector3 Acl, float Damp, float M) : Particle(Pos, Vel, Acl, Damp, M) {}
	~Proyectil() {}

private:
};

