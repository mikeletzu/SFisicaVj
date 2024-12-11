#pragma once
#include "Particle.h"
class ParticleShape :
    public Particle
{
public:
	ParticleShape(Vector3 Pos, Vector3 Vel, Vector3 Acl, float Damp, float M, float LifeTime, bool isCube = true, Vector4 Col = {1.0, 1.0, 1.0, 1.0}, Vector3 BoxSize = {1.0, 1.0, 1.0}) : Particle(Pos, Vel, Acl, Damp, M, LifeTime) {
		pose = physx::PxTransform(Pos);
		_boxSize = BoxSize;
		DeregisterRenderItem(renderItem);
		if (isCube)
			renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(BoxSize.x, BoxSize.y, BoxSize.z)), &pose, Col);
		else
			renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pose, Col);
	}
	~ParticleShape() {}

	float getHeight() { return _boxSize.y; }
	float getVol() { return _boxSize.x * _boxSize.y * _boxSize.z; }

private:
	Vector3 _boxSize;
};

