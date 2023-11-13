#include "UniformParticleGenerator.h"
#include "Firework.h"
#include <random>
//constructora
UniformParticleGenerator::UniformParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel) {
	stdDevPos = std_dev_pos;
	stdDevVel = std_dev_vel;
}
//destructora
UniformParticleGenerator::~UniformParticleGenerator() {}

list<Particle*> UniformParticleGenerator::generateParticles(int type) {
	switch (type)
	{
	case 4:
		return generatefirework1();
	default:
		break;
	}
    
}
std::list<Particle*>  UniformParticleGenerator::generatefirework1() {
	std::list<Particle*> particles;

	for (int i = 0; i < _n_particles; i++) {
		// Genera posiciones y velocidades muestreadas de una distribución gaussiana
		Vector3 Vel =  Vector3(0, dis(_mt) * stdDevVel.y, 0);
		Vector3 Pos = _origin + Vector3(dis(_mt) * stdDevPos.x, dis(_mt) * stdDevPos.y, dis(_mt) * stdDevPos.z);
		float time = dis1(_mt);
		float radio = 0.6;
		Vector4 Col(0.655, 0.804, 0.91,1);
		particles.push_back(new Particle(Pos, Vel, Vector3(0, 0, 0), 0.2f, Col, time, radio, 0));
	}

	return particles;
};
