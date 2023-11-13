#pragma once
#include "ParticleForceRegistry.h"

	void ParticleForsceRegistry::updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}
	void ParticleForsceRegistry::addRegistry(ForceGenerator* fg, Particle* p) { //registra una particula
		auto range = equal_range(fg);
		bool exists = false;
		auto it = range.first;
		while (it != range.second) {
			if (it->second == p) {
				exists = true;
				break;
			}
			++it;
		}

		// Si no existe, insertar
		if (!exists) {
			insert(FRPair(fg, p));
		}

		//this->insert(FRPair(fg, p));
	}
	void ParticleForsceRegistry::deleteParticleRegistry(Particle* p) {//borra una particula
		auto it = begin();
		while (it != end())
		{
			if (it->second != p) ++it;
			else it = this->erase(it);
		}
	}