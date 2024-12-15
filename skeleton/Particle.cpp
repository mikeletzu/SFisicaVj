#include "Particle.h"
#include <iostream>

void Particle::integrate(double t)
{
	//EULER
	/*pose.p += vel * dt;
	vel += acl * dt;
	vel *= 1 - damp;
	t += dt;*/

	//VERLET
	acl = forceAcum*mass;
	vel = (vel + (acl * t / 2));
	pose.p += vel * t + 0.5 * ((acl - (damp*vel)) / mass) * pow(t, 2);

	std::cout << "Pose y: " << pose.p.y << std::endl;
	
	clearForce();
	lifeTime -= t;
}
