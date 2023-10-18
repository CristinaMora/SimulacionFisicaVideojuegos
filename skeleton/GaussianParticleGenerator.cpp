#include "GaussianParticleGenerator.h"

#include <random>
//constructora
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel) {
	stdDevPos = std_dev_pos;
	stdDevVel = std_dev_vel;
}
//destructora
GaussianParticleGenerator::~GaussianParticleGenerator() {}
double GaussianParticleGenerator::generateGaussianValue(double mean, double stddev) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}

list<Particle*> GaussianParticleGenerator::generateParticles() {
    std::list<Particle*> particles;

    for (int i = 0; i < _n_particles; i++) {
        // Genera posiciones y velocidades muestreadas de una distribución gaussiana
		Vector3 Vel = _mean_velocity + Vector3(_u(_mt) * stdDevVel.x, _u(_mt) * stdDevVel.y, _u(_mt) * stdDevVel.z);
		Vector3 Pos = _origin + Vector3(_u(_mt), _u(_mt), _u(_mt));
		int time = dis2(_mt);
		int r = dis2(_mt);
		int mas = 3;
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

        particles.push_back(new Particle(Pos, Vel, Vector3(0, -9.8, 0),mas, Col, time));
    }

    return particles;
}
