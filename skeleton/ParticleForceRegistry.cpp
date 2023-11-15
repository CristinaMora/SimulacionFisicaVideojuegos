#pragma once
#include "ParticleForceRegistry.h"

	void ParticleForsceRegistry::updateForces(double duration) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, duration);
		}
	}
	void ParticleForsceRegistry::addRegistry(ForceGenerator* fg, Particle* p) { //registra una particula
		
			insert(FRPair(fg, p));
		

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