#include "GravityForceGenerator.h"
void GravityForceGenerator::updateForce(Particle*p, double t) {
	if (fabs((1/p->getMass()) < 1e-10)) {
		return;
	}
	p->addForce(_gravity * p->getMass());
	
}
bool GravityForceGenerator::updateForce(physx::PxRigidBody* solid, double t) {
	if (fabs((1 / solid->getMass()) < 1e-10)) {
		return true;
	}
	
	solid->addForce(_gravity * solid->getMass());
	return true;
}

