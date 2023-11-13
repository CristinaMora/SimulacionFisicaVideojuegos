#include "ParticleSystem.h"
	
	ParticleSystem::ParticleSystem(const Vector3& g) {
		// Creates a void system with a det. gravity
		//_gravity = g;
		_firework_generator = new UniformParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
		_particle_generators.push_back(_firework_generator);
		_firework_generator = new GaussianParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
		_particle_generators.push_back(_firework_generator);
		_pFR = new ParticleForsceRegistry();
		_gravity_force_generator = new GravityForceGenerator({0,-9.8f,0});
		listOfForceGenerators.push_back(_gravity_force_generator);
		_WindofChange_Force_Generator = new WindofChangeForceGenerator({6,0,0},{10,0,0},{10,5,5},10 , 0);
		listOfForceGenerators.push_back(_WindofChange_Force_Generator);
	};

	//destructora de la clase
	ParticleSystem::~ParticleSystem() {
		

			for (auto e : _particles)
			{
				delete e;
			}
			_particles.clear();
			for (auto e : _firework_pool) {
				delete e;
			}
			_firework_pool.clear();
			for (auto e : _particle_generators)
			{
				_particle_generators.pop_front();
			}
			delete _gravity_force_generator;
			delete _WindofChange_Force_Generator;
		
	};

	// Integrates the particles and checks for its lifetime, etc!
	void ParticleSystem::update(double t){
		
		_pFR->updateForces(t); 
		//actualiza las particulas y las elimina en caso de que esten muertas
		
		//lista de generadores fuentes
		/*for (auto gen : _particle_generators) {
			std::list<Particle*> lista = gen->generateParticles();
			for (auto partic : lista) {
				_particles.push_back(partic);
			}
			
		}*/
		//lista de particulas, se actualizan, explotan...
		list<Particle*>::iterator e = _particles.begin();
		while (e != _particles.end()) {
			auto aux = e;
			++aux;

			if ((*e)->integrate(t)) {

				if ((*e)->_type >= 1) {

					Firework* firework = static_cast<Firework*>(*e);
					std::list<Particle*> p = firework->explode();

					for (auto d : p) {
						_particles.push_back(d);

					}
				}
				onParticleDeath(*e);
			}
			else {
				_pFR->addRegistry(_gravity_force_generator, *e);
				_pFR->addRegistry(_WindofChange_Force_Generator, *e);
			}
			e = aux;
		
		}

	};
	// Method to generate a Firework with the appropiate type
	void ParticleSystem::generateFirework(unsigned firework_type, Vector3 pos,Vector3 vel, Vector3 acel, double masa,float t,Vector4 c, int radio){
		_part = new Firework(pos, vel, acel, masa, t, c, radio, firework_type);
		_particles.push_back(_part);
		if(firework_type!=4) _part->addGenerator(_particle_generators.back());
		else _part->addGenerator(_particle_generators.front());

	};
	// Gets a particle generator with name
	ParticleGenerator* ParticleSystem::getParticleGenerator(const string& n){
		
		return nullptr;
	};


	//! This is used currently in the Fireworks to spread more Fireworks!
	void ParticleSystem::onParticleDeath(Particle* particleaa){
		
		//quitarlo del multimap
		_pFR->deleteParticleRegistry(particleaa);
		_particles.remove(particleaa);
		 delete (particleaa);
		

	};
	void ParticleSystem::createFireworkSystem() {

	};
