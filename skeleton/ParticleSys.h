#pragma once
#include <list>
#include <random>
#include <iostream>
#include "Particle.h"

class ParticleSys
{
public:
	ParticleSys() {};
	void fuente();

private:
	std::list<Particle*> myPops;
};

