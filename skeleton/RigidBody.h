#pragma once
#include "RenderUtils.hpp"
using namespace std;
using namespace physx;
//CLASE BASE SOLIDOS RIGIDOS 
class RigidBody
{
	public:
		PxRigidBody* body;
		RenderItem* item;
		PxShape* shape;
		float time = 0;
		float tolive;
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
