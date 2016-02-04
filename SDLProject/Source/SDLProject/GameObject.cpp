//====================================================================================================
// Filename:	GameObject.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "GameObject.h"
#include "AABBCollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "CollisionSystem.h"

//====================================================================================================
// Typedef
//====================================================================================================
#define Collision CollisionSystem::Instance()

//====================================================================================================
// Class Definitions
//====================================================================================================

GameObject::GameObject()
	: mLayer(0)
	, mName("New Game Object")
	, mVelocity(Vector2())
	, mSpeed(0.0f)
{
	mpSprite = new Sprite();
	mpAABBCol = nullptr;
	mpBoxCol = nullptr;
	mpCircleCol = nullptr;
}

//----------------------------------------------------------------------------------------------------

GameObject::~GameObject()
{
	Destroy();
}

//----------------------------------------------------------------------------------------------------

void GameObject::Update()
{
	mpSprite->Update();
}

//----------------------------------------------------------------------------------------------------

void GameObject::Destroy()
{
	// Do clean-up
	if (mpAABBCol != nullptr)
	{
		Collision.RemoveCollider(mpAABBCol);
		delete mpAABBCol;
	}
	if (mpBoxCol != nullptr)
	{
		Collision.RemoveCollider(mpBoxCol);
		delete mpBoxCol;
	}
	if (mpCircleCol != nullptr)
	{
		Collision.RemoveCollider(mpCircleCol);
		delete mpCircleCol;
	}
	delete mpSprite;
}

//----------------------------------------------------------------------------------------------------

void GameObject::HandleCollision(GameObject* other)
{
	// To be overloaded by sub-classes
}

//----------------------------------------------------------------------------------------------------

void GameObject::AddCollider(ColliderTypes::Type type)
{
	switch(type)
	{
	case (ColliderTypes::AABB):
		{
			mpAABBCol = new AABBCollider(this, GetWidth() * 0.8f, GetHeight());
			break;
		}
	case (ColliderTypes::Box):
		{
			mpBoxCol = new BoxCollider(this, GetWidth() * 0.8f, GetHeight());
			break;
		}
	case (ColliderTypes::Circle):
		{
			mpCircleCol = new CircleCollider(this, GetWidth() * 0.5f);
			break;
		}
	default:	break;
	}
}

//----------------------------------------------------------------------------------------------------

void GameObject::SetSprite(const char* fileName)
{
	mpSprite->SetTexture(fileName);
}

//----------------------------------------------------------------------------------------------------

void GameObject::SetAnimation(const char* fileName, AnimState::State state)
{
	mpSprite->LoadAnimation(fileName);
	mpSprite->SetAnimState(state);
}

//----------------------------------------------------------------------------------------------------

void GameObject::SetActiveCollider(bool active)
{
	// Update Collider
	if (mpAABBCol != nullptr)
	{
		mpAABBCol->SetActive(active);
	}
	if (mpBoxCol != nullptr)
	{
		mpBoxCol->SetActive(active);
	}
	if (mpCircleCol != nullptr)
	{
		mpCircleCol->SetActive(active);
	}
}

//----------------------------------------------------------------------------------------------------

void GameObject::UpdateCollider()
{
	if (mpAABBCol != nullptr)
	{
		mpAABBCol->Update();
	}
	if (mpBoxCol != nullptr)
	{
		mpBoxCol->Update();
	}
	if (mpCircleCol != nullptr)
	{
		mpCircleCol->Update();
	}
}