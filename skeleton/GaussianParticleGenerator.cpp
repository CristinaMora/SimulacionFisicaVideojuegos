#include "GaussianParticleGenerator.h"
//constructora
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel, Particle* p) {
	stdDevPos = std_dev_pos;
	stdDevVel = std_dev_vel;
	_model_particle = p;
}
//destructora
GaussianParticleGenerator::~GaussianParticleGenerator() {}
list<Particle*> GaussianParticleGenerator::generateParticles() {

	list<Particle*> particles;

	for (int i = 0; i < 1; i++) {
		Particle* p = _model_particle->clone();

		double randomValue = _u(_mt);
		if (randomValue <= _generation_prob) {
			p->setPos(_model_particle->getPos().p + Vector3(_u(_mt) * stdDevPos.x, _u(_mt) * stdDevPos.y, _u(_mt) * stdDevPos.z));
			p->setVel(_model_particle->getVel() + Vector3(_u(_mt) * stdDevVel.x, _u(_mt) * stdDevVel.y, _u(_mt) * stdDevVel.z));
			cout << _u(_mt) << " \n";
			particles.push_back(p);
		}
	}
	return particles;
}
