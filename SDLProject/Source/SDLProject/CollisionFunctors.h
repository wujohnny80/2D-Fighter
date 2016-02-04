//====================================================================================================
// Filename:	CollisionFunctors.h
// Created by:	Johnny Wu
// Description:	Collider functors
//====================================================================================================
#ifndef _COLLISIONFUNCTORS_H_
#define _COLLISIONFUNCTORS_H_

#include "Math.h"

#include "AABBCollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Collider.h"

namespace CollisionFunctors
{

inline bool AABB(Collider* const _a, Collider* _b)
{
	AABBCollider* a = reinterpret_cast<AABBCollider*>(_a);
	AABBCollider* b = reinterpret_cast<AABBCollider*>(_b);

	return Math::Intersect(a->mRect, b->mRect);
}

inline bool AABBBox(Collider* const _a, Collider* _b)
{
	// TODO Change to rotating box collision
	return AABB(_a, _b);
}

inline bool AABBCircle(Collider* const _a, Collider* _b)
{
	AABBCollider* a = reinterpret_cast<AABBCollider*>(_a);
	CircleCollider* b = reinterpret_cast<CircleCollider*>(_b);
	return Math::Intersect(a->mRect, b->mCircle);
}

inline bool BoxAABB(Collider* const _a, Collider* _b)
{
	// TODO Change to rotating box collision
	return AABB(_a, _b);
}

inline bool BoxBox(Collider* const _a, Collider* _b)
{
	// TODO Change to rotating box collision
	return AABB(_a, _b);
}

inline bool BoxCircle(Collider* const _a, Collider* _b)
{
	// TODO Change to rotating box collision
	return AABBCircle(_a, _b);
}

inline bool CircleAABB(Collider* const _a, Collider* _b)
{
	// TODO Change to rotating box collision
	CircleCollider* a = reinterpret_cast<CircleCollider*>(_a);
	AABBCollider* b = reinterpret_cast<AABBCollider*>(_b);
	return Math::Intersect(a->mCircle, b->mRect);
}

inline bool CircleBox(Collider* const _a, Collider* _b)
{
	// TODO Change to rotating box collision
	return CircleAABB(_a, _b);
}

inline bool CircleCircle(Collider* const _a, Collider* _b)
{
	CircleCollider* a = reinterpret_cast<CircleCollider*>(_a);
	CircleCollider* b = reinterpret_cast<CircleCollider*>(_b);
	return Math::Intersect(a->mCircle, b->mCircle);
}

}

#endif // #ifndef _COLLISIONFUNCTORS_H_