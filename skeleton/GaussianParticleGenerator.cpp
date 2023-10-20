#include "GaussianParticleGenerator.h"
#include "Firework.h"
#include <random>
//constructora
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel) {
	stdDevPos = std_dev_pos;
	stdDevVel = std_dev_vel;
}
//destructora
GaussianParticleGenerator::~GaussianParticleGenerator() {}

list<Particle*> GaussianParticleGenerator::generateParticles(int type) {
	switch (type)
	{
	case 4:
		return generatefirework1();
	default:
		break;
	}
    
}
std::list<Particle*>  GaussianParticleGenerator::generatefirework1() {
	std::list<Particle*> particles;

	for (int i = 0; i < _n_particles; i++) {
		// Genera posiciones y velocidades muestreadas de una distribución gaussiana
		Vector3 Vel = _mean_velocity + Vector3(0, dis(_mt) * stdDevVel.y, dis(_mt) * stdDevVel.z);
		float time = dis1(_mt);
		float radio = 0.6;
		Vector4 Col(1, 0.978, 0, 1);
		particles.push_back(new Particle(_origin, Vel, Vector3(0, -9.8, 0), 3, Col, time, radio, 0));
	}

	return particles;
};

