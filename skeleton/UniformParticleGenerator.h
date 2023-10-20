#pragma once
#include "ParticleGenerator.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;
using namespace physx;
class UniformParticleGenerator: public ParticleGenerator
{
	public:
		UniformParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
		virtual ~UniformParticleGenerator();
		virtual std::list<Particle*> generateParticles(int type) override;
		std::list<Particle*> generatefirework1();
		std::list<Particle*> generatefirework2();
		std::list<Particle*> generatefirework3();
		
	protected:
	private:
		std::uniform_real_distribution<float> dis{ 1, 3 }; //esta es de tipo normal
		std::uniform_real_distribution<float> dis1{ 0.6, 1.7 };
		std::uniform_int_distribution<int> dis2{ 0, 10 };
		Vector3 stdDevPos, stdDevVel;


};

	
