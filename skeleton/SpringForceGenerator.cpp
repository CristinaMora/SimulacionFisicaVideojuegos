#pragma once
#include "SpringForceGenerator.h"
SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) {
		_k = k;
		_resting_length = resting_length;
		_other = other;
	}
SpringForceGenerator::SpringForceGenerator(double resting_length, physx::PxRigidStatic* _other,double k) {
	_k = k;
	_resting_length = resting_length;
	_other2 = _other;
}
void SpringForceGenerator::updateForce(Particle* particle, double t) {
	Vector3 relative_pos_vector = _other->getPos() - particle->getPos();
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;
	Vector3 force = relative_pos_vector * delta_x * _k;
	particle->addForce(force);
}
bool SpringForceGenerator::updateForce(physx::PxRigidBody* solid, double t) {
	Vector3 relative_pos_vector = _other2->getGlobalPose().p - solid->getGlobalPose().p;
	relative_pos_vector.y = 0;
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;
	Vector3 force = relative_pos_vector * delta_x * _k;
	solid->addForce(force);
	return true;
}
SpringForceGenerator::~SpringForceGenerator() {}

