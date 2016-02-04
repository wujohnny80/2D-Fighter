//====================================================================================================
// Filename:	CircleCollider.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "CircleCollider.h"
#include <iostream>

//====================================================================================================
// Class Definitions
//====================================================================================================

CircleCollider::CircleCollider(GameObject* owner, float radius)
	: Collider(owner)
{
	mCircle.center = PositionCenter();
	mCircle.radius = radius;
}

//----------------------------------------------------------------------------------------------------

CircleCollider::~CircleCollider()
{
}

//----------------------------------------------------------------------------------------------------

void CircleCollider::Update()
{
	mCircle.center = PositionCenter();
	mCircle.radius = CurrentSize().x * 0.5f;
}