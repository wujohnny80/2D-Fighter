//====================================================================================================
// Filename:	CircleCollider.h
// Created by:	Johnny Wu
// Description:	Class for circle colliders
//====================================================================================================
#ifndef _CIRCLECOLLIDER_H_
#define _CIRCLECOLLIDER_H_

#include "Collider.h"
#include "Circle.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CircleCollider : public Collider
{
public:
	CircleCollider(GameObject* owner, float radius);
	~CircleCollider();

	void Update();

	Circle mCircle;
};

#endif // #ifndef _CIRCLECOLLIDER_H_