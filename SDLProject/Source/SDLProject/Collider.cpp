//====================================================================================================
// Filename:	Collider.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Collider.h"
#include "CollisionFunctors.h"
#include "CollisionSystem.h"
#include "GameObject.h"

#define Collision CollisionSystem::Instance()
//====================================================================================================
// Class Definitions
//====================================================================================================

Collider::Collider(GameObject* const owner)
	: mpOwner(owner)
	, mOffset(Vector2())
	, mActive(true)
{
	// Construct functor map
	mFunctors["class AABBCollider class AABBCollider"] = CollisionFunctors::AABB;
	mFunctors["class AABBCollider class BoxCollider"] = CollisionFunctors::AABBBox;
	mFunctors["class AABBCollider class CircleCollider"] = CollisionFunctors::AABBCircle;
	mFunctors["class BoxCollider class AABBCollider"] = CollisionFunctors::BoxAABB;
	mFunctors["class BoxCollider class BoxCollider"] = CollisionFunctors::BoxBox;
	mFunctors["class BoxCollider class CircleCollider"] = CollisionFunctors::BoxCircle;
	mFunctors["class CircleCollider class AABBCollider"] = CollisionFunctors::CircleAABB;
	mFunctors["class CircleCollider class BoxCollider"] = CollisionFunctors::CircleBox;
	mFunctors["class CircleCollider class CircleCollider"] = CollisionFunctors::CircleCircle;
	
	// Add to collision system
	Collision.AddColliders(this);
}

//----------------------------------------------------------------------------------------------------

Collider::~Collider()
{
}

//----------------------------------------------------------------------------------------------------

void Collider::Update()
{
	// To be implemented by sub-class
}

//----------------------------------------------------------------------------------------------------

Vector2 Collider::PositionTL()
{
	return mpOwner->GetSprite()->TopLeft() + mOffset;
}

//----------------------------------------------------------------------------------------------------

Vector2 Collider::PositionCenter()
{
	return mpOwner->GetSprite()->Center() + mOffset;
}

//----------------------------------------------------------------------------------------------------

Vector2 Collider::CurrentSize()
{
	return Vector2(mpOwner->GetWidth(), mpOwner->GetHeight());
}

//----------------------------------------------------------------------------------------------------

bool Collider::IsColliding(Collider* other)
{
	std::string strPair = typeid((*this)).name();
	strPair.append(" ");
	strPair.append(typeid(*other).name());

	return mFunctors[strPair](this, other);
}