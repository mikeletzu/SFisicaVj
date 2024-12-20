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
#include "WhirlGenerator.h"


enum PSType
{
	fog, explosion, snow, springs, buoyancy, camera, trail, goal
};


class ParticleSys
{
public:
	ParticleSys(PSType type, RigidDinBody* anch = nullptr);
	void update(double t);
	void generate(int amount);
	bool eraseCheck(Particle* p);
	void addForce(ForceGenerator* f);
	Particle* getCamPop();

private:
	Zone* _zone;
	std::list<Particle*> myPops;
	std::list<ForceGenerator*> myForces;
	PopForceRegistry myForceReg;

	//Media, Desviación y Posición
	Vector3 vM, vD, aM, aD, pM, pD;
	int lifeTimeM, lifeTimeD;
	bool isOutZone(Vector3 p);
	int interval;
	PSType _type;
	RigidDinBody* toTrail = nullptr;

	void generateSpringAnchDemo();
	void generateSpringDuoDemo();
	void generateHairTieDemo();
	void generateBuoyancyDemo();

	void generateGameSnow(int amount);
};

/*

	Labores de mantenimiento de las partículas
		• Actualizar el tiempo que lleva “vivo”
		• Recorrer la lista de partículas y revisar si cada una de ellas ha de
		seguir viva o no:
			• Se ha terminado su tiempo de vida
			• Está fuera de la zona de interés
		• Eliminar las partículas que “mueren”
		• Llamar al update de cada partícula

	Labores de generación de partículas nuevas
		• Recorrer los distintos generadores
		• Generar las partículas nuevas
		• Añadirlas a la lista de partículas

*/

