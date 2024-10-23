#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acl, float Damp, float M, float LifeTime) : vel(Vel), acl(Acl), damp(Damp), mass(M), lifeTime(LifeTime){
		pose = physx::PxTransform(Pos);
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pose, { 1.0, 1.0, 1.0, 1.0 });
	}
	~Particle() {}

	void integrate(double t);

protected:
	float damp, mass, lifeTime;
	Vector3 vel, acl;
	physx::PxTransform pose; //se le pasa a render item la * d esta pose para que se actualize automáticamente
	RenderItem* renderItem;
};

