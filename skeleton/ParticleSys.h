#pragma once
#include <list>
#include <random>
#include <iostream>
#include "Particle.h"
#include "Zone.h"

enum PSType
{
	fog, explosion, snow
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
	std::list<Particle*> myPops;
	Zone* _zone;
	//Media, Desviación y Posición
	Vector3 vM, vD, aM, aD, pM, pD;
	int lifeTimeM, lifeTimeD;
	bool isOutZone(Vector3 p);
	int interval;
	PSType _type;
	std::list<ForceGenerator*> forces;
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

