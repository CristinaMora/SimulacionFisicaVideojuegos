#pragma once
#include "ParticleGenerator.h"
#include <iostream>
#include <time.h>
using namespace std;
using namespace physx;
class GaussianParticleGenerator: public ParticleGenerator
{
	public:
		GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
		virtual ~GaussianParticleGenerator();
		virtual std::list<Particle*> generateParticles() override;
		double GaussianParticleGenerator::generateGaussianValue(double mean, double stddev);
	protected:
	private:
		std::random_device rd;
		std::uniform_int_distribution<int> dis{ 0, 2 };
		std::uniform_int_distribution<int> dis2{ 0, 10 };
		Vector3 stdDevPos, stdDevVel;
		double stdDevTime;


};

	
