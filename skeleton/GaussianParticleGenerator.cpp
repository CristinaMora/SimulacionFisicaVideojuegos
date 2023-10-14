#include "GaussianParticleGenerator.h"

#include <random>
//constructora
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel, Particle* p) {
	stdDevPos = std_dev_pos;
	stdDevVel = std_dev_vel;
	_model_particle = p;
}
//destructora
GaussianParticleGenerator::~GaussianParticleGenerator() {}
list<Particle*> GaussianParticleGenerator::generateParticles() {
	std::mt19937 gen(rd());

	list<Particle*> particles;

	for (int i = 0; i < 1; i++) {
		Particle* p = _model_particle->clone();

		double randomValue = _u(_mt);
		if (randomValue <= _generation_prob) {
			p->setPos(_model_particle->getPos().p + Vector3(_u(_mt) * stdDevPos.x, _u(_mt) * stdDevPos.y, _u(_mt) * stdDevPos.z));
			p->setVel(_model_particle->getVel() + Vector3(_u(_mt) * stdDevVel.x, _u(_mt) * stdDevVel.y, _u(_mt) * stdDevVel.z));
			p->settime(dis2(gen));
			int r = dis(gen);
			switch (r)
			{
			case 0:
				p->setCol(Vector4(0 , 1 , 0.3, 1));
				break;
			case 1:
				p->setCol(Vector4(0 , 0.2 , 1, 1));
				break;
			case 2:
				p->setCol(Vector4(0.4 , 0 , 1, 1));
				break;
			case 3:
				p->setCol(Vector4(0.5 , 0.2 , 0,1));
				break;
			case 4:
				p->setCol(Vector4(0.7 , 0 , 0, 1));
				break;
			case 5:
				p->setCol(Vector4(0.8 , 1 , 0.2, 1));
				break;
			case 6:
				p->setCol(Vector4(1 , 0 , 0.5, 1));
				break;
			case 7:
				p->setCol(Vector4(0.9, 0.5, 0.2, 1));
				break;
				
			default:
				break;
			}
			particles.push_back(p);
		}
	}
	return particles;
}
