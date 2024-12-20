#pragma once
#include "WindGenerator.h"

class RigidDinBody;
class Particle;

class WhirlGenerator :
    public WindGenerator
{
public:
    WhirlGenerator(float k1, float k2, Vector3 a, Vector3 b, Vector3 f, Vector3 pos, bool active = true) :
        WindGenerator(k1, k2, a, b, f, active) {
        _pos = pos;
    };
    virtual void update(Particle* pop, double t) override;
    virtual void update(RigidDinBody* pop, double t) override;

private:
    Vector3 _pos;
};

