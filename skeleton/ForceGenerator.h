#pragma once
#include "core.hpp"

class RigidDinBody;

class Particle;

class ForceGenerator
{
protected:
	bool _active;
	Vector3 _f;

public:
	ForceGenerator(Vector3 f, bool active) : _active(active), _f(f) { };
	virtual void update(Particle* pop, double t);
	virtual void update(RigidDinBody* pop, double t);
	inline void setActive(bool a) { _active = a; };
	inline bool getActive() { return _active; };
};

