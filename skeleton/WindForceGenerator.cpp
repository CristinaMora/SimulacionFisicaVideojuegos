#pragma once
#include "WindForceGenerator.h"
#include <iostream>
#include <string>

using namespace std;
WindForceGenerator::WindForceGenerator(Vector3 fuerzaViento, Vector3 origen, Vector3 tam, const float k1, const float k2) : ParticleDragGenerator(k1, k2) {
		f = fuerzaViento;
		porigen = origen;
		size = tam; 
		 
	}
	void WindForceGenerator::updateForce(Particle* particle, double t){

		


		Vector3 pp = particle->getPos().p;
		if ((pp.x >= porigen.x && pp.x <= porigen.x + size.x) && (pp.y >= porigen.y && pp.y <= porigen.y + size.y) && (pp.z >= porigen.z && pp.z <= porigen.z + size.z)) {
			if (fabs(1 / particle->masa) < 1e-10) return;
		
			Vector3 v = particle->getVel();
			Vector3 diff = f - v;
			Vector3 dragF;
			dragF = _k1 * diff + _k2 * diff.magnitude() * diff;

			particle->addForce(dragF);


		}
		else return;
		
	}
