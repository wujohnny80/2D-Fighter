//====================================================================================================
// Filename:	AABBCollider.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "AABBCollider.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

AABBCollider::AABBCollider(GameObject* owner, float width, float height)
	: Collider(owner)
{
	mRect.x = PositionTL().x;
	mRect.y = PositionTL().y;
	mRect.w = width;
	mRect.h = height;
}

//----------------------------------------------------------------------------------------------------

AABBCollider::~AABBCollider()
{
}

//----------------------------------------------------------------------------------------------------

void AABBCollider::Update()
{
	mRect.x = PositionTL().x;
	mRect.y = PositionTL().y;
	mRect.w = CurrentSize().x;
	mRect.h = CurrentSize().y;
}