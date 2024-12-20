#include "Particle.h"
#include <iostream>

void Particle::integrate(double t)
{
	//EULER
	vel += (forceAcum / mass) * t;
	vel *= 1 - damp;
	pose.p += vel * t;

	//VERLET
	/*
	acl = forceAcum / mass;
	vel = (vel + (acl * t / 2));
	pose.p += vel * t + 0.5 * ((acl - (damp*vel)) / mass) * pow(t, 2);
	*/

	clearForce();
	lifeTime -= t;
}
