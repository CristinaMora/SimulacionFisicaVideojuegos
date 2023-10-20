#pragma once
#include "ParticleGenerator.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;
using namespace physx;
class GaussianParticleGenerator: public ParticleGenerator
{
	public:
		GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
		virtual ~GaussianParticleGenerator();
		virtual std::list<Particle*> generateParticles(int type) override;
		list<Particle*> generatefirework1();
		
	protected:
	private:
		
		normal_distribution<float> dis{ 0, 1 }; 
		normal_distribution<float> dis1{ 1, 3 };
		Vector3 stdDevPos, stdDevVel;


};

	
