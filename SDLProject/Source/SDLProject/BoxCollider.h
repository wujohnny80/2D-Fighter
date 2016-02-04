//====================================================================================================
// Filename:	BoxCollider.h
// Created by:	Johnny Wu
// Description:	Class for box colliders
//====================================================================================================
#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include "Collider.h"
#include "Rect.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* owner, float width, float height);
	~BoxCollider();

	void Update();

	Rect mRect;
};

#endif // #ifndef _BOXCOLLIDER_H_