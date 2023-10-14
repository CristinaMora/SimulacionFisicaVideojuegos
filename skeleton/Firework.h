#pragma once
#include "Particle.h"
#include <list>
class ParticleGenerator;
using namespace std;
class Firework
{
public:
	// The firework generates more fireworks when exploding --> they should be gathered by the System
		list<Particle*> explode();
	void addGenerator(ParticleGenerator* p);
	virtual Particle* clone() const; 
protected:
		// Type
		unsigned _type;
private:

	//list<shared_ptr<ParticleGenerator> > _gens;
};

