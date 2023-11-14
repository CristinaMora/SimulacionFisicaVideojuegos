#pragma once
#include "WindofChangeForceGenerator.h"
class whirlwind: public WindofChangeForceGenerator
{
public: 
	whirlwind(Vector3 fuerza,const float k, Vector3 WhirlPos, Vector3 tam_);
	~whirlwind() {}
	void updateForce(Particle* particle, double t) override;
private:
	
};


