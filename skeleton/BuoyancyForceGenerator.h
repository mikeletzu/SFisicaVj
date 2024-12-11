#pragma once
#include "ForceGenerator.h"
#include "ParticleShape.h"

class BuoyancyForceGenerator :
    public ForceGenerator
{
public:
	BuoyancyForceGenerator(float d, Vector3 pos); //pos para la superficie del agua
	virtual void updateForce(Particle* particle, double t);
	virtual ~BuoyancyForceGenerator();
	void addMass(float m);

protected:
	float _liquid_density;
	float _gravity = 9.8;

	//falta meterle esa particle de referencia a renderizar y mierdas
	ParticleShape* _liquid_particle; //for representation

};

