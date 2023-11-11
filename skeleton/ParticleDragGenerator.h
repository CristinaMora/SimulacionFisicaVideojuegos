#pragma once
#include "ForceGenerator.h"
#include"core.hpp"
class ParticleDragGenerator : public ForceGenerator {
public:
	ParticleDragGenerator();
	ParticleDragGenerator(const float k1, const float k2);
	virtual void updateForce(Particle* particle, double t);
	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
	inline float getk1() { return _k1; }
	inline float getk2() { return _k2; }
protected:
	float _k1;
	float _k2;
};