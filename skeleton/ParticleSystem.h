#pragma once
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "WindForceGenerator.h"
class ParticleSystem
{
	public:
		// Creates a void system with a det. gravity
		ParticleSystem();
		virtual ~ParticleSystem();
		// Integrates the particles and checks for its lifetime
		void update(double t);
		// Method to generate a Firework with the appropiate type
		void generateFirework(unsigned firework_type, Vector3 pos, Vector3 vel, Vector3 acel, double masa, float t, Vector4 c, int radio);
		void generateParticle(unsigned dorcetype, Vector3 pos, Vector3 vel, Vector3 acel, double masa, float t, Vector4 c, int radio);
		void createscene(PxScene* gScene, PxPhysics* gPhysics);
		void Deleteforce();
		void addforce();

	protected:
		Particle* p1 = nullptr;
		Particle* p2 = nullptr;
		Particle* p3 = nullptr;
		

		int k = 5;
		Firework* _part = nullptr;
		list <Particle*> _particles;
		list<Firework*> _firework_pool;
		list <ParticleGenerator*> _particle_generators; 
		ParticleGenerator* _firework_generator; 
		Vector3 _gravity;
		void onParticleDeath(Particle * p);

		//FUERZAS
		list<ForceGenerator*> listOfForceGenerators;
		ParticleForsceRegistry* _pFR;
		WindForceGenerator* _Wind_Force_Generator;
		GravityForceGenerator* _gravity_force_generator;
		GravityForceGenerator* _gravityMoon_force_generator;
private:
	//objetos para la creacion de la escena:
	RenderItem* base;

	PxRigidStatic* suelo;
	PxShape* shape;

};