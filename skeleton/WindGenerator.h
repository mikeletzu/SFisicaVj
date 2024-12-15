#pragma once
#include "ForceGenerator.h"
#include "Zone.h"

class WindGenerator :
    public ForceGenerator
{
public:
    WindGenerator(float k1, float k2, Vector3 minZone, Vector3 maxZone, Vector3 f, bool active = true) : 
        _k1(k1), _k2(k2), ForceGenerator(f, active) { _zone = new Zone(minZone, maxZone); };
    virtual void update(Particle* pop, double t) override;
    virtual void update(RigidDinBody* pop, double t) override;

protected:
    float _k1;
    float _k2;
    Zone* _zone;
};

