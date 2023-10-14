#include "GaussianParticleGenerator.h"
//constructora
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel) {}
//destructora
GaussianParticleGenerator::~GaussianParticleGenerator() {}
list<Particle*> GaussianParticleGenerator::generateParticles() {

	list<Particle*> particles;

	for (int i = 0; i < 3; i++) {
		auto* p = model->clone();

		double randomValue = _mt();
		if (randomValue <= _generation_prob) {
			p->setPos(model->getPos() + Vector3(_u(_mt) * stdDevPos.x, _u(_mt) * stdDevPos.y, _u(_mt) * stdDevPos.z));
			p->setVel(model->getVel() + Vector3(_u(_mt) * stdDevVel.x, _u(_mt) * stdDevVel.y, _u(_mt) * stdDevVel.z));

			int paletteSize;


			particles.push_back(p);
		}
	}
	return particles;
}
