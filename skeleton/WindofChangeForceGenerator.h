
#pragma once
#include "ParticleDragGenerator.h"
class WindofChangeForceGenerator : public ParticleDragGenerator {
public:
	WindofChangeForceGenerator(Vector3 fuerzaViento, Vector3 origen, Vector3 tam, const float k1, const float k2);
	Vector3 f;
	void updateForce(Particle* particle, double t) override;
private:
	Vector3 porigen, size;
};