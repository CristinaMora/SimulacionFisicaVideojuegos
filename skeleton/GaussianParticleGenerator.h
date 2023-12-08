#pragma once
#include "ParticleGenerator.h"
#include "Firework.h"
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
		std::list<Particle*> generatefirework1();
		std::list<Particle*> generatefirework2();
		std::list<Particle*> generatefirework3();
		
	protected:
	private:
		
		normal_distribution<float> dis{ 1, 3 }; 
		normal_distribution<float> dis1{ 0.6, 0.7 };
		normal_distribution<float> dis2{ 0, 10 };
		Vector3 stdDevPos, stdDevVel;


};
	
