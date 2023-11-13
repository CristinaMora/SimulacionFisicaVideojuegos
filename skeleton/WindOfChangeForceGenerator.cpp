#pragma once
#include "WindOfChangeForceGenerator.h"

WindofChangeForceGenerator::WindofChangeForceGenerator(Vector3 fuerzaViento, Vector3 origen, Vector3 tam, const float k1, const float k2) : ParticleDragGenerator(k1, k2) {
		f = fuerzaViento;
		porigen = origen;
		size = tam;
	}
	void WindofChangeForceGenerator::updateForce(Particle* particle, double t){
		Vector3 pp = particle->getPos().p;
		if (pp.x > 10) {
			Vector3 vresult = (f - particle->getVel());
		}
		if ((pp.x >= porigen.x && pp.x <= porigen.x + size.x) && (pp.y >= porigen.y && pp.y <= porigen.y + size.y) && (pp.z >= porigen.z && pp.z <= porigen.z + size.z)) {
			if (fabs(1 / particle->masa) < 1e-10) return;
			Vector3 vresult = (f - particle->getVel());
			//compute drag force
			Vector3 dragF = _k1 * vresult + _k2 * vresult * vresult.magnitude();
			particle->addForce(dragF);
		}
		else return;
		
	}
