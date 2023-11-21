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
	case 1:
		return generatefirework1();
	case 2:
		return generatefirework2();

	case 3:
		return generatefirework3();
	
	default:
		break;
	}
    
}


std::list<Particle*>  GaussianParticleGenerator::generatefirework1() {
	std::list<Particle*> particles;

	for (int i = 0; i < _n_particles; i++) {

		Vector3 Vel = _mean_velocity + Vector3(_u(_mt) * stdDevVel.x, _u(_mt) * stdDevVel.y, 0);
		Vector3 Pos = _origin + Vector3(_u(_mt), _u(_mt), _u(_mt));
		float time = dis(_mt);
		float radio = abs(dis1(_mt));
		int r = dis2(_mt);
		Vector4 Col;
		switch (r)
		{
		case 0:
			Col = Vector4(0, 1, 0.3, 1);
			break;
		case 1:
			Col = (Vector4(0, 0.2, 1, 1));
			break;
		case 2:
			Col = (Vector4(0.4, 0, 1, 1));
			break;
		case 3:
			Col = (Vector4(0.5, 0.2, 0, 1));
			break;
		case 4:
			Col = (Vector4(0.7, 0, 0, 1));
			break;
		case 5:
			Col = (Vector4(0.8, 1, 0.2, 1));
			break;
		case 6:
			Col = (Vector4(1, 0, 0.5, 1));
			break;
		case 7:
			Col = (Vector4(0.9, 0.5, 0.2, 1));
			break;

		default:
			Col = (Vector4(0.7, 0.5, 0.6, 1));

			break;
		}

		particles.push_back(new Particle(Pos, Vel, Vector3(0,0, 0), 0.2f, Col, time, radio, 0));
	}

	return particles;
};
std::list<Particle*>  GaussianParticleGenerator::generatefirework2() {
	std::list<Particle*> particles;

	for (int i = 0; i < _n_particles; i++) {
		// Genera posiciones y velocidades muestreadas de una distribución gaussiana
		Vector3 Vel = _mean_velocity + Vector3(_u(_mt) * stdDevVel.x, _u(_mt) * stdDevVel.y, _u(_mt) * stdDevVel.z);
		Vector3 Pos = _origin + Vector3(_u(_mt), _u(_mt), _u(_mt));
		float time = dis(_mt);
		float radio = abs( dis1(_mt));
		Vector4 Col = (Vector4(0.4, 0, 1, 1));
		
		Firework* fire = new Firework(Pos, Vel, Vector3(0, 0, 0), 0.2f, time, Col, radio, 1);
		particles.push_back(fire);
		fire->addGenerator(this);

	}

	return particles;
};
std::list<Particle*>  GaussianParticleGenerator::generatefirework3() {
	std::list<Particle*> particles;

	for (int i = 0; i < _n_particles; i++) {

		float time = dis(_mt);
		float radio = 1.04f;
		Vector4 Col{0.961, 0.255, 0.729,1 };


		// Genera posiciones en forma de corazón
		float t = 2.0f * (3.14159) * _u(_mt);
		float x = 16.0f * sin(t) * sin(t) * sin(t);
		float y = 13.0f * cos(t) - 5.0f * cos(2 * t) - 2.0f * cos(3 * t) - cos(4 * t);
		Vector3 Pos = _origin + Vector3(0, y, x);

		// Genera velocidades en función de la posición
		Vector3 distanceToCenter = Pos - _origin;
		Vector3 Vel = _mean_velocity + distanceToCenter;

		// Resto de tu código para el tiempo, color, etc.

		particles.push_back(new Particle(Pos, Vel, Vector3(0, 0, 0), 0.2f, Col, time, radio, 0));

	}

	return particles;
};