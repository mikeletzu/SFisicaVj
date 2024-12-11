#pragma once
#include "SpringGenerator.h"
class HairTieGenerator :
    public SpringGenerator
{
public:
    HairTieGenerator(Particle* anchor, float k, float l0, bool active = true) :
        SpringGenerator(anchor, k, l0, active) {};
    virtual void update(Particle* pop, double t) override;
};

