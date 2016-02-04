//====================================================================================================
// Filename:	BoxCollider.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "BoxCollider.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

BoxCollider::BoxCollider(GameObject* owner, float width, float height)
	: Collider(owner)
{
	mRect.x = PositionTL().x;
	mRect.y = PositionTL().y;
	mRect.w = width;
	mRect.h = height;
}

//----------------------------------------------------------------------------------------------------

BoxCollider::~BoxCollider()
{
}

//----------------------------------------------------------------------------------------------------

void BoxCollider::Update()
{
	mRect.x = PositionTL().x;
	mRect.y = PositionTL().y;
	mRect.w = CurrentSize().x;
	mRect.h = CurrentSize().y;
}