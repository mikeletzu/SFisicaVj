#pragma once
#include <list>
#include <random>
#include <iostream>
#include "Particle.h"

enum PSType
{
	fog, explosion
};


class ParticleSys
{
public:
	ParticleSys(PSType type);
	void update(double t);
	void generate(int amount);

private:
	std::list<Particle*> myPops;
	std::pair<Vector3, Vector3> zone;
	//Media, Desviaci�n y Posici�n
	Vector3 vM, vD, aM, aD, pM, pD;
	int lifeTimeM, lifeTimeD;
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

