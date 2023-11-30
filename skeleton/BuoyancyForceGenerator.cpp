#include "BuoyancyForceGenerator.h"
#include <iostream>
BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d,Vector3 pos) :posicion(pos) {
	_height = h;
	_volume = V;
	_liquid_density = d;
	RenderItem* _renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(10.0f, 10.0f, 10.0f)), &posicion, { 0.2,0.4,0.6,1.0 });

	_liquid_particle = new Particle(_renderItem, posicion, { 0,0,0 }, 10, 15, 0);


}
 void BuoyancyForceGenerator::updateForce(Particle* particle, double t) {
	float h = particle->getPos().p.y;
	float h0 = _liquid_particle->getPos().p.y;
	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5)
	{
		immersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		immersed = 1.0;
	}
	else
	{
		immersed = (h0 - h) / _height + 0.5;
	}
	f.y = _liquid_density * _volume * immersed * _gravity;
	particle->addForce(f);
}
 BuoyancyForceGenerator::~BuoyancyForceGenerator() {}
