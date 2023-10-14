#pragma once
#include "Particle.h"
#include <list>
class ParticleGenerator;
using namespace std;
class Firework: public  Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas,float t, Vector4 c);
	virtual ~Firework() {};
	// The firework generates more fireworks when exploding --> they should be gathered by the System
		//list<Particle*> explode();
	//void addGenerator(ParticleGenerator* p);
	//virtual Particle* clone() const; 
protected:
		// Type
		unsigned _type;
private:
	bool firework = true;
	//list<shared_ptr<ParticleGenerator> > _gens;
};

