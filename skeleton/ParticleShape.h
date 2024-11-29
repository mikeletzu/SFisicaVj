#pragma once
#include "Particle.h"
class ParticleShape :
    public Particle
{
public:
	ParticleShape(Vector3 Pos, Vector3 Vel, Vector3 Acl, float Damp, float M, float LifeTime) : Particle(Pos, Vel, Acl, Damp, M, LifeTime) {
		pose = physx::PxTransform(Pos);
		DeregisterRenderItem(renderItem);
		renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(1.0, 1.0, 1.0)), &pose, { 1.0, 1.0, 1.0, 1.0 });
	}
	~ParticleShape() {}

private:
};

