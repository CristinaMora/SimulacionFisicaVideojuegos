#include "whirlwind.h"
void whirlwind::updateForce(Particle* particle, double t) {
	Vector3 pp = particle->getPos().p;
	if (pp.x > 10) {
		Vector3 vresult = (f - particle->getVel());
	}
	
	Vector3 dragF = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 p = particle->getPos().p;
	if (p.y > 60.0f) {
		Vector3 f = _k1 * Vector3(-(p.z - porigen.z), 50 - (p.y - porigen.y),p.x - porigen.x);
		Vector3 v = particle->getVel() - f;
		float drag_coef = v.normalize();
		drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
		dragF = -v * drag_coef;
	}
	particle->addForce( dragF);
}


