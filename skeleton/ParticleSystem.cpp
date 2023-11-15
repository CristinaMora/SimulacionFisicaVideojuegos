#include "ParticleSystem.h"
	
	ParticleSystem::ParticleSystem() {
		_firework_generator = new UniformParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
		_particle_generators.push_back(_firework_generator);
		_firework_generator = new GaussianParticleGenerator(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
		_particle_generators.push_back(_firework_generator);
		_pFR = new ParticleForsceRegistry();

		
		_gravity_force_generator = new GravityForceGenerator({0,-9.8f,0});
		listOfForceGenerators.push_back(_gravity_force_generator);
		_gravityMoon_force_generator = new GravityForceGenerator({ 0,-1.62f,0 });
		listOfForceGenerators.push_back(_gravityMoon_force_generator);
		_Wind_Force_Generator = new WindForceGenerator({0,0,3.0f},{ 0, 0, -100 },{ 100, 100, 50 },1.0f , 0);
		listOfForceGenerators.push_back(_Wind_Force_Generator);
		whirlwindfChange_Force_Generator = new whirlwind({0.7f,0.03f,0.03f }, 2.0f,{10,0,0}, { 10,5,5 });
		listOfForceGenerators.push_back(whirlwindfChange_Force_Generator);
		_explosion_force_generator = new ExplosionForceGenerator(10000,300, {0,20,0},900,100);
		listOfForceGenerators.push_back(_explosion_force_generator);


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
			delete _Wind_Force_Generator;
			delete whirlwindfChange_Force_Generator;
			delete _explosion_force_generator;
		
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
			e = aux;
		
		}
		

	};
	// Method to generate a Firework with the appropiate type
	void ParticleSystem::generateFirework(unsigned firework_type, Vector3 pos,Vector3 vel, Vector3 acel, double masa,float t,Vector4 c, int radio){
		_part = new Firework(pos, vel, acel, masa, t, c, radio, firework_type);
		_particles.push_back(_part);
		if(firework_type!=4) _part->addGenerator(_particle_generators.back());
		else _part->addGenerator(_particle_generators.front());
		_pFR->addRegistry(_gravity_force_generator, _part);
		//_pFR->addRegistry(_Wind_Force_Generator, _part);
		//_pFR->addRegistry(whirlwindfChange_Force_Generator, _part);
		

	};
	void ParticleSystem::generateParticle(unsigned forcetype, Vector3 pos, Vector3 vel, Vector3 acel, double masa, float t, Vector4 c, int radio) {
		Particle* p = new Particle(pos, vel, acel, masa, c, t, radio, 0);
		_particles.push_back(p);
		switch (forcetype)
		{
			case 1: //gravedad
				_pFR->addRegistry(_gravity_force_generator, p);
				break;
			case 2: //gravedad luna
				_pFR->addRegistry(_gravityMoon_force_generator, p);
				break;
			case 3: //viento
				_pFR->addRegistry(_Wind_Force_Generator, p);
				break;
			case 4: //tornado
				_pFR->addRegistry(whirlwindfChange_Force_Generator, p);
				break;
			default:
				break;
		}


	};


	//destructora de las particulas
	void ParticleSystem::onParticleDeath(Particle* particleaa){
		
		//se borran del multi map, de la lista y se llama a la destructora de la particula
		_pFR->deleteParticleRegistry(particleaa);
		_particles.remove(particleaa);
		 delete (particleaa);
		

	};
	void ParticleSystem::createscene() {
		//suelgo gris
		base = new RenderItem(CreateShape(PxBoxGeometry(500, 1, 500)), new PxTransform(0, 0,0), { 0.51f, 0.486f, 0.455f,1.0f });
		//cuadrado de viento  {10,0,0},{10,5,5} orig tam
		//cuadviento = new RenderItem(CreateShape(PxBoxGeometry(100, 100, 50)), new PxTransform(0, 20, -100), { 1.0f, 0.251f, 0.42f, 0.361f });
		
	
	};
