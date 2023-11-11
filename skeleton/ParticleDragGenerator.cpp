#include "ParticleDragGenerator.h"

 void ParticleDragGenerator::updateForce(Particle* particle, double t) {
	if (fabs((1/particle->masa)) < 1e-10) return;
	//compute drag force
	Vector3 v = particle->getVel();
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	particle->addForce(dragF);
}