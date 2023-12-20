#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "RenderUtils.hpp"
#include <list>
#include "PxShape.h"
#include "UniformParticleGenerator.h"
#include "WindForceGenerator.h"
#include "GravityForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "SolidForceRegistry.h"
#include "ExplosionForceGenerator.h"

using namespace physx;
class RBManager
{
	public:
		RBManager(PxPhysics* gPhysics, PxScene* gScene);
		virtual ~RBManager();
		 RigidBody addDynamicObject(float Cestatico, float Cdinamico, float Elastico, PxVec3 inertiaT, Vector3 dimension,
			Vector4 color, Vector3 transform, Vector3 velocity, Vector3 angularvelocity, float density, int timetoleave, bool ball=false, const char* name = "");
		 Pala* addPalas(bool l, Vector3 transform, const char* name);
		 StaticRigidBody addStaticObject(Vector3 dimension, Vector4 color, Vector3 transform, PxQuat rotate, bool ball=false, const char* name="");
		void createscene();
		void createsplosion(RigidBody p1, Vector3 pos);
		void update(double t);
		void addForce();
		void keypress(unsigned char key);
		bool fin = false;
	private:
		
		std::list<RigidBody> _objects;
		std::list<StaticRigidBody> _statics;
		UniformParticleGenerator* _generator;
		WindForceGenerator* windForceGen;
		GravityForceGenerator* gravityForceGen;
		GravityForceGenerator* gravityForceGenContra;
		AnchoredSpringFG* anchoredForceGen;
		PxPhysics* _gPhysics;
		PxScene* _gScene;
		SolidForceRegistry* _sFR;

		bool tenso = false;
		//cosas del pinball:
		//palaI
		Pala* palaI;
		 
		//palaD
		Pala* palaD;
		
		//bola
		RigidBody bola;
		//muelle
		RigidBody muelle;


		int num = 0;
		

};
