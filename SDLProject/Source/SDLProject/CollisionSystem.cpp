//====================================================================================================
// Filename:	CollisionSystem.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "CollisionSystem.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CollisionSystem::CollisionSystem()
	: mInitialized(false)
{
}

//----------------------------------------------------------------------------------------------------

void CollisionSystem::Initialize(int winWidth, int winHeight)
{
	mQuadTree.Initialize(winWidth, winHeight);
	mInitialized = true;
}

//----------------------------------------------------------------------------------------------------

void CollisionSystem::Update()
{
	unsigned int s = mColliders.size();
	for (unsigned int i = 0; i < s; ++i)
	{
		mQuadTree.Insert(mColliders[i]);
	}
	mQuadTree.Update();
	mQuadTree.Clear();
}

//----------------------------------------------------------------------------------------------------

void CollisionSystem::Terminate()
{
	auto it = mColliders.begin();
	for(;it != mColliders.end(); ++it)
	{
		*it = nullptr;
	}
	mInitialized = false;
}

//----------------------------------------------------------------------------------------------------

void CollisionSystem::AddColliders(Collider* collider)
{
	mColliders.push_back(collider);
}

//----------------------------------------------------------------------------------------------------

void CollisionSystem::RemoveCollider(Collider* collider)
{
	auto it = mColliders.begin();
	for(;it != mColliders.end(); ++it)
	{
		if ((*it) == collider)
		{
			*it = nullptr;
		}
	}
}