#pragma once
#include "ForceGenerator.h"
#include "Particle.h"
#include "RigidDinBody.h"

class SpringGenerator :
    public ForceGenerator
{
public:
    SpringGenerator(Particle* pAnchor, RigidDinBody* rbAnchor, float k, float l0, bool active = true) :
       _pAnchor(pAnchor), _rbAnchor(rbAnchor), _k(k), _l0(l0), ForceGenerator({1.0, 1.0, 1.0}, active) {};
    virtual void update(Particle* pop, double t) override;

    inline void setK(double k) { _k = k; }
    
protected:
    float _k;
    float _l0;
    Particle* _pAnchor;
    RigidDinBody* _rbAnchor;
};

