//====================================================================================================
// Filename:	AABBCollider.h
// Created by:	Johnny Wu
// Description:	Class for AABB colliders
//====================================================================================================
#ifndef _AABBCOLLIDER_H_
#define _AABBCOLLIDER_H_

#include "Collider.h"
#include "Rect.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class AABBCollider : public Collider
{
public:
	AABBCollider(GameObject* owner, float width, float height);
	~AABBCollider();

	void Update();

	Rect mRect;
};

#endif // #ifndef _AABBCOLLIDER_H_