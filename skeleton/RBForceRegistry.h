#pragma once
#include <map>
#include "RigidDinBody.h"
#include "ForceGenerator.h"

class RBForceRegistry :
    public std::multimap<RigidDinBody*, ForceGenerator*>
{
public:
    RBForceRegistry();
    void add(RigidDinBody* pop, ForceGenerator* fgen) {
        auto it = insert({ pop, fgen });
    }
};

