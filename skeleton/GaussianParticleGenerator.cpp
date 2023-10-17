#include "GaussianParticleGenerator.h"

#include <random>
//constructora
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel) {
	stdDevPos = std_dev_pos;
	stdDevVel = std_dev_vel;
}
//destructora
GaussianParticleGenerator::~GaussianParticleGenerator() {}
list<Particle*> GaussianParticleGenerator::generateParticles() {
	
	list<Particle*> particles;

	for (int i = 0; i < _n_particles; i++) {
		//double randomValue = _u(_mt);
		//if (randomValue <= _generation_prob) {
			Vector3 Vel = _mean_velocity + Vector3(_u(_mt) * stdDevVel.x, _u(_mt) * stdDevVel.y, _u(_mt) * stdDevVel.z);
			Vector3 Pos = _origin + Vector3(_u(_mt) , _u(_mt) , _u(_mt) );
			int time = dis2(_mt);
			int r = dis(_mt);
			int mas = 3;
			Vector4 Col;
			switch (r)
			{
			case 0:
				Col = Vector4(0 , 1 , 0.3, 1);
				break;
			case 1:
				Col = (Vector4(0 , 0.2 , 1, 1));
				break;
			case 2:
				Col = (Vector4(0.4 , 0 , 1, 1));
				break;
			case 3:
				Col = (Vector4(0.5 , 0.2 , 0,1));
				break;
			case 4:
				Col = (Vector4(0.7 , 0 , 0, 1));
				break;
			case 5:
				Col = (Vector4(0.8 , 1 , 0.2, 1));
				break;
			case 6:
				Col =(Vector4(1 , 0 , 0.5, 1));
				break;
			case 7:
				Col = (Vector4(0.9, 0.5, 0.2, 1));
				break;
				
			default:
				break;
			}
			
			Particle *p = new Particle( Pos,  Vel, Vector3(0, -3.8, 0),  mas,  Col,  time);
			particles.push_back(p);

		//}
	}
	return particles;
}
