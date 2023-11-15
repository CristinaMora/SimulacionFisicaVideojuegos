#include "whirlwind.h"
void whirlwind::updateForce(Particle* particle, double t) {
	Vector3 pp = particle->getPos().p;
	//if ((pp.x >= porigen.x && pp.x <= porigen.x + size.x) && (pp.y >= porigen.y && pp.y <= porigen.y + size.y) && (pp.z >= porigen.z && pp.z <= porigen.z + size.z)) {
		if (fabs(1 / particle->masa) < 1e-10) return;
			Vector3 velocidadtorvellino = _k1 * Vector3(-(pp.z - porigen.z), 75 - (pp.y - porigen.y), pp.x - porigen.x);
			Vector3 v = particle->getVel() - velocidadtorvellino;
			float drag_coef = v.normalize();
			drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
			Vector3 dragF = -v * drag_coef;

		particle->addForce(dragF);

	//}
}
//Vector3 fuerzaViento, 
whirlwind::whirlwind(Vector3 fuerza, const float k, Vector3 WhirlPos, Vector3 tam_): WindForceGenerator( fuerza, WhirlPos, tam_, k, 0) {

}


