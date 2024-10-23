#include "Particle.h"

void Particle::integrate(double t)
{
	float dt = 1.0f;
	float mass = 1.0f;

	while (t <= 10.0)
	{
		//EULER
		/*pose.p += vel * dt;
		vel += acl * dt;
		vel *= 1 - damp;
		t += dt;*/

		//VERLET
		pose.p += vel * dt + 0.5 * ((acl - (damp*vel)) / mass) * pow(dt, 2);
		vel += 0.5 * acl / mass * dt;
		t += dt;
	}
	lifeTime -= t;
	if (lifeTime <= 0) {
		//ME ELIMINO
		//AL SALIR DE LA ZONA QUIERO ELIMINARME TMBN
	}
}
