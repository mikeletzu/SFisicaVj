#pragma once
#include "ForceGenerator.h"
#include "Zone.h"

class WindGenerator :
    public ForceGenerator
{
public:
    WindGenerator(float k1, float k2, Vector3 minZone = { -999999.0,  -999999.0,  -999999.0 }, Vector3 maxZone = { 999999.0,  999999.0,  999999.0 }, Vector3 f = { 0.0, 0.0, 0.0 }, bool active = true) :
        _k1(k1), _k2(k2), ForceGenerator(f, active) { _zone = new Zone(minZone, maxZone); };
    virtual void update(Particle* pop, double t) override;
    virtual void update(RigidDinBody* pop, double t) override;
    inline void makeTorqued() { withTorque = true; }

protected:
    float _k1;
    float _k2;
    Zone* _zone;
    bool withTorque = false;
};

