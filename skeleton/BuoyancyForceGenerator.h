#pragma once
#include "ForceGenerator.h"
#include "PxPhysics.h"
#include "PxShape.h"
#include "RenderUtils.hpp"
class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float V, float d);
	virtual void updateForce(Particle* particle, double t);
	virtual ~BuoyancyForceGenerator();
protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;
	Particle* _liquid_particle;
	physx::PxTransform posicion;
};

