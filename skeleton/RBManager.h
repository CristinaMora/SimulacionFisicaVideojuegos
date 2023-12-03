#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "RenderUtils.hpp"
#include "UniformParticleGenerator.h"
#include "WindForceGenerator.h"
#include <list>
#include "PxShape.h"
#include "SolidForceRegistry.h"


using namespace physx;
class RBManager
{
	public:
		RBManager(PxPhysics* gPhysics, PxScene* gScene);
		virtual ~RBManager();
		void addDynamicObject();
		void addStaticObject();
		void update(double t);
		void addForce();
	private:
		
		std::list<RigidBodyWithTime> _objects;
		UniformParticleGenerator* _generator;
		//RigidForceRegistry* reg;
		WindForceGenerator* windForceGen;
		
		PxPhysics* _gPhysics;
		PxScene* _gScene;
		PxRigidDynamic* object;
		SolidForceRegistry* _sFR;
		
		int num = 0;
		

};
