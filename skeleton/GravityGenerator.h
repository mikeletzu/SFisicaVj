#pragma once
#include "ForceGenerator.h"

class Particle;

class GravityGenerator :
    public ForceGenerator
{
public:
    GravityGenerator(Vector3 f, bool active = true) : ForceGenerator(f, active) {};
    virtual void update(Particle* pop, double t) override;
    virtual void update(RigidDinBody* pop, double t) override;
};

