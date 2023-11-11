#include "GravityForceGenerator.h"
void GravityForceGenerator::updateForce(Particle*p, double t) {
	if (fabs((1/p->masa) < 1e-10)) {
		return;
	}
	p->addForce(_gravity * p->masa);
}
