#pragma once
#include "SpringForceGenerator.h"
SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) {
		_k = k;
		_resting_length = resting_length;
		_other = other;
	}
void SpringForceGenerator::updateForce(Particle* particle, double t) {
	Vector3 relative_pos_vector = _other->getPos().p - particle->getPos().p;
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;
	Vector3 force = relative_pos_vector * delta_x * _k;
	particle->addForce(force);
}
SpringForceGenerator::~SpringForceGenerator() {}
