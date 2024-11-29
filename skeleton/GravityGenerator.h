#pragma once
#include "ForceGenerator.h"
class GravityGenerator :
    public ForceGenerator
{
public:
    GravityGenerator(Vector3 f, bool active = true) : ForceGenerator(f, active) {};
};

