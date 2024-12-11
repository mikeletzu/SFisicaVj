#include "RigidDinBody.h"

RigidDinBody::RigidDinBody(physx::PxScene* scene, physx::PxPhysics* phys, Vector4 color, physx::PxTransform Pos,
	Vector3 LinearVel, Vector3 AngularVel, float lifetime, float Density, bool isBox, Vector3 boxSize, float Dam) :
	_gScene(scene), _gPhysics(phys), _density(Density), _size(boxSize)
	{
		physx::PxRigidDynamic* new_solid;
		new_solid = _gPhysics->createRigidDynamic(Pos);
		new_solid->setLinearVelocity(LinearVel);
		new_solid->setAngularVelocity(AngularVel);
		new_solid->setLinearDamping(Dam);

		physx::PxShape* shape = nullptr;
		if (isBox) {
			shape = CreateShape(physx::PxBoxGeometry(boxSize.x, boxSize.y, boxSize.z));
		}
		else {
			shape = CreateShape(physx::PxSphereGeometry(boxSize.x));
		}
		new_solid->attachShape(*shape);

		_renderItem = new RenderItem(shape, new_solid, color);
		_gScene->addActor(*new_solid);
		
		_body = new_solid;

		// Calculo automatico:
		// physx::PxRigidBodyExt::updateMassAndInertia(*new_solid, Density);
		// Calculo a mano:
		float mass = _density * boxSize.x * boxSize.y * boxSize.z;
		float iH = (1 / 12) * mass * (boxSize.x * boxSize.x + boxSize.z * boxSize.z);
		float iW = (1 / 12) * mass * (boxSize.z * boxSize.z + boxSize.y * boxSize.y);
		float iD = (1 / 12) * mass * (boxSize.x * boxSize.x + boxSize.y * boxSize.y);
		_body->setMassSpaceInertiaTensor({iH,iW,iD});
		
	}

RigidDinBody::~RigidDinBody()
{
}
