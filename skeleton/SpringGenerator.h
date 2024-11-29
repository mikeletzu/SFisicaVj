#pragma once
#include "ForceGenerator.h"
#include "Particle.h"

class SpringGenerator :
    public ForceGenerator
{
public:
    SpringGenerator(Particle* anchor, float k,  Vector3 f, bool active = true) :
        _k(k), ForceGenerator(f, active) {
    };
    virtual void update(Particle* pop, double t) override;

    void initL0(Vector3 popPos);
    
protected:
    float _k;
    float _l0;
    Particle* anchor;
};

