#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, Vector3 anchor_pos) : SpringForceGenerator(k, resting, nullptr), posicion(anchor_pos) {
		//particula en forma cuadrada
	
		RenderItem * _renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(10.0f, .2f, 10.0f)), &posicion, {0.2,0.4,0.6,1.0 });
		
		_other = new Particle(_renderItem, posicion, { 0,0,0 }, 10, 15, 0);

	}
AnchoredSpringFG::~AnchoredSpringFG() {
		delete _other;
	
};