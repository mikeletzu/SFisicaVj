#pragma once
#include "core.hpp"
#include <list>
#include "RenderUtils.hpp"
#include "ForceGenerator.h"
#include <iostream>

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acl, float Damp, float M, float LifeTime) : 
		vel(Vel), acl(Acl), damp(Damp), mass(M), lifeTime(LifeTime){
		forceAcum = { 0, 0, 0 };
		pose = physx::PxTransform(Pos);
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pose, { 1.0, 1.0, 1.0, 1.0 });
	}
	~Particle() { DeregisterRenderItem(renderItem); }

	void integrate(double t);
	float getLT() { return lifeTime; };
	Vector3 getPos() { return pose.p; };
	Vector3 getVel() { return vel; };
	float getMass() { return mass; };
	Vector3 setVel(Vector3 v) { vel = v; };
	inline void addForce(Vector3 f) { forceAcum += f;};
	inline void clearForce() { forceAcum *= 0; };

protected:
	float damp, mass, lifeTime;
	Vector3 vel, acl, forceAcum;
	physx::PxTransform pose; //se le pasa a render item la * d esta pose para que se actualize automáticamente
	RenderItem* renderItem;
};

