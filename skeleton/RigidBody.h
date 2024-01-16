#pragma once
#include "RenderUtils.hpp"
#include <iostream>
using namespace std;
using namespace physx;
//CLASE BASE SOLIDOS RIGIDOS 
#define degToRad(angleInDegrees) ((angleInDegrees) * PxPi / 180.0)
class RigidBody
{
	public:
		RigidBody() {};
		PxRigidDynamic* body;
		RenderItem* item;
		PxShape* shape;
		float time = 0;
		float tolive;
		RigidBody(PxRigidDynamic* _body, RenderItem* _item, PxShape* _shape) : body(_body), item(_item), shape(_shape) {};

		 
};
class StaticRigidBody
{
public:
	PxRigidStatic* body;
	RenderItem* item;
	PxShape* shape;
	Vector4 color;
	float time = 0;
	StaticRigidBody(PxRigidStatic* _body, RenderItem* _item, PxShape* _shape, const Vector4& _color)
		: body(_body), item(_item), shape(_shape), color(_color) {}

};
//class Pala:public RigidBody {
//	public:
//		Pala(): RigidBody() {}
//		~Pala() {}
//		bool left;
//		PxVec3 iniPos; //posicion inicial
//		const float  speed = .08f;
//		const PxVec3 rise = PxVec3(0, 0, 0);
//		float lerp = 0;
//		void Update(double t) {
//			lerp += GetAsyncKeyState(left ? 'N' : 'C') ? -speed : speed;
//			lerp = PxClamp<float>(lerp, 0, 1);
//			//cambias la posición + cuanto queremos que sume * 
//
//			body->setKinematicTarget(PxTransform(iniPos + lerp * rise,
//				PxQuat(degToRad(pow(-1, left) * -20 * (lerp )), PxVec3(0, 1, 0))));
//			//                                                        en que eje
//		}
//};
