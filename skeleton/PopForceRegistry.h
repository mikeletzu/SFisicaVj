#pragma once
#include <map>
#include "Particle.h"
#include "ForceGenerator.h"

class PopForceRegistry :
    public std::multimap<Particle*, ForceGenerator*>
{
public:
    PopForceRegistry();
    void add(Particle* pop, ForceGenerator* fgen) {
        auto it = insert({ pop, fgen });
    }
};

