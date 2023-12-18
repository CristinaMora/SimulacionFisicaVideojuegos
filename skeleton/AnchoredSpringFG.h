#pragma once
#include "SpringForceGenerator.h"
#include "PxPhysics.h"
#include "PxShape.h"
#include "RenderUtils.hpp"
class AnchoredSpringFG : public SpringForceGenerator {
public:
	AnchoredSpringFG(double k, double resting, Vector3 anchor_pos);
	AnchoredSpringFG(double k, double resting, Vector3 anchor_pos, PxPhysics* gPhysics, PxScene* gScene);
	virtual ~AnchoredSpringFG();
};