#pragma once
#include "ParticleGenerator.h"
#include <time.h>
using namespace std;
using namespace physx;
class GaussianParticleGenerator: public ParticleGenerator
{
	public:
		GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel, Particle* p);
		virtual ~GaussianParticleGenerator();
		virtual list<Particle*> generateParticles();
	protected:
	private:
		Vector3 stdDevPos, stdDevVel;
		double stdDevTime;


};

	
