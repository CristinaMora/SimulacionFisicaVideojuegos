#pragma once
#include "Particle.h"
#include <list>
class ParticleGenerator;
using namespace std;
class Firework: public  Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 aceler, int mas,float t, Vector4 c, float radio, int type);
	virtual ~Firework();

	 bool integrate(float t);
	// The firework generates more fireworks when exploding --> they should be gathered by the System
	 std::list<Particle*> explode();
	 void addGenerator(ParticleGenerator* p);
	 //virtual Particle* clone() const;
protected:
private:
	bool firework = true;
	list<ParticleGenerator*> _gens;
};

