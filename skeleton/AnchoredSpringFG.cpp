#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, Vector3 anchor_pos) : SpringForceGenerator(k, resting, nullptr) {
		_other = new Particle(anchor_pos, { 0,0,0 }, { 0,0,0 }, 10, { 0.2,0.4,0.6,1.0 }, 15, { 10.0f, 0.2f, 10.0f }, 0);

	}
AnchoredSpringFG::~AnchoredSpringFG() {
		delete _other;
	
};