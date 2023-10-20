#pragma once
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "Firework.h"
class ParticleSystem
{
	public:
		// Creates a void system with a det. gravity
		ParticleSystem(const Vector3& g = { 0.0f, -3.8, 0.0f});
		virtual ~ParticleSystem();
		// Integrates the particles and checks for its lifetime, etc!
		void update(double t);
		// Method to generate a Firework with the appropiate type
		void generateFirework(unsigned firework_type, Vector3 pos, Vector3 vel, Vector3 acel, int masa, float t, Vector4 c, int radio);
		void generateParticleGenerator();
		//void generateFirework(unsigned firework_type);
		// Gets a particle generator with name...
		ParticleGenerator* getParticleGenerator(const string& n);
	protected:
		list <Particle*> _particles;
		Firework* _part = nullptr;
		list<Firework*> _firework_pool;
		list <ParticleGenerator*> _particle_generators; // These are the registred generators(for on demand set generation prob.to 0)
		ParticleGenerator* _firework_generator; // This generator is only to shoot the firework!!
		Vector3 _gravity;
			//! This is used currently in the Fireworks to spread more Fireworks!
		void onParticleDeath(Particle * p);
		void createFireworkSystem();
};