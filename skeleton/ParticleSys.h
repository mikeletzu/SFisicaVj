#pragma once
#include <list>
#include <random>
#include <iostream>
#include "ParticleShape.h"
#include "Zone.h"
#include "HairTieGenerator.h"
#include "GravityGenerator.h"
#include "PopForceRegistry.h"
#include "BuoyancyForceGenerator.h"


enum PSType
{
	fog, explosion, snow, springs, buoyancy
};


class ParticleSys
{
public:
	ParticleSys(PSType type);
	void update(double t);
	void generate(int amount);
	bool eraseCheck(Particle* p);
	void addForce(ForceGenerator* f);

private:
	Zone* _zone;
	std::list<Particle*> myPops;
	std::list<ForceGenerator*> myForces;
	PopForceRegistry myForceReg;

	//Media, Desviaci�n y Posici�n
	Vector3 vM, vD, aM, aD, pM, pD;
	int lifeTimeM, lifeTimeD;
	bool isOutZone(Vector3 p);
	int interval;
	PSType _type;

	void generateSpringAnchDemo();
	void generateSpringDuoDemo();
	void generateHairTieDemo();
	void generateBuoyancyDemo();
};

/*

	Labores de mantenimiento de las part�culas
		� Actualizar el tiempo que lleva �vivo�
		� Recorrer la lista de part�culas y revisar si cada una de ellas ha de
		seguir viva o no:
			� Se ha terminado su tiempo de vida
			� Est� fuera de la zona de inter�s
		� Eliminar las part�culas que �mueren�
		� Llamar al update de cada part�cula

	Labores de generaci�n de part�culas nuevas
		� Recorrer los distintos generadores
		� Generar las part�culas nuevas
		� A�adirlas a la lista de part�culas

*/

