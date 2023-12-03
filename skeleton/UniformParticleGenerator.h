#pragma once
#include "ParticleGenerator.h"
#include <iostream>
#include <random>
#include <time.h>
using namespace std;
	//solidos rigidos

class UniformParticleGenerator: public ParticleGenerator
{
	public:
		UniformParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
		UniformParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel, PxPhysics* gPhysics, PxScene* gScene);
		virtual ~UniformParticleGenerator();
		virtual std::list<Particle*> generateParticles(int type) override;
		list<Particle*> generatefirework1();
		list<RigidBodyWithTime>generateSolidRigid();
	
	private:
		std::uniform_real_distribution<float> dis{ 0, 1 };
		std::uniform_real_distribution<float> dis1{ 1, 3};
		Vector3 stdDevPos, stdDevVel;

		PxPhysics* _gPhysics;
		PxScene* _gScene;
		int nsolid=10;
};

	
