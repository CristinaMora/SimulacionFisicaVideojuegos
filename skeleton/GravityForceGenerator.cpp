#include "GravityForceGenerator.h"
void GravityForceGenerator::updateForce(Particle*p, double t) {
	if (fabs(p->_inv_mass < 1e-10)) {
		return;
	}
	p->addForce(_gravity * p->mass);
}