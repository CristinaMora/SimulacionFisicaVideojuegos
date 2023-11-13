#pragma once
#include "WindofChangeForceGenerator.h"
class whirlwind: public WindofChangeForceGenerator
{
public: 
	whirlwind(const float k, Vector3 WhirlPos, double Duration);
	~whirlwind() {}
	void updateForce(Particle* particle, double t) override;
private:
	
};


