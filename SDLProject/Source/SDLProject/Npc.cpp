//====================================================================================================
// Filename:	Npc.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Npc.h"
#include "Math.h"
#include "Application.h"
#include <iostream>

//====================================================================================================
// Class Definitions
//====================================================================================================

Npc::Npc(bool leftSide)
	: GameObject()
	, mpHealthBar(nullptr)
	, mMaxHealth(100)
	, mLeftSide(leftSide)
	, mpTarget(nullptr)
	, mHard(false)
	, mElapsedTime(0)
	, mTime(0)
	, mPrevTime(0)
{
	mHealth = mMaxHealth;
	mVelocity.x = 1.0f;
	mDirection = rand() % 2;
	if (mDirection == 1) ChangeDirection();
	mSpeed = 5.0f;
	
	Position().y = 700;
	if (mLeftSide)
		Position().x = 200;
	else
		Position().x = 1080;
}

//----------------------------------------------------------------------------------------------------

void Npc::Update()
{	
	mTime = SDL_GetTicks(); // Gives time in milliseconds
	if (mHealth <= 0 && State() != AnimState::Death)
	{
		SetAnimState(AnimState::Death);
	}

	Position().x += mVelocity.x * mSpeed;
	Position().y -= mVelocity.y * mSpeed;

	UpdateAI();
	SetState();

	// Update Sprite
	mpSprite->Update();
	
	// Update Collider
	UpdateCollider();
	
	mPrevTime = mTime;	// Set previous time
}

//----------------------------------------------------------------------------------------------------

void Npc::HandleCollision(GameObject* other)
{
	if (!mpTarget)
		mpTarget = other;

	// If I'm in attack state
	if (State() == AnimState::Punch || State() == AnimState::Kick || State() == AnimState::Special)
	{
		SetActiveCollider(false);
		// Check which side enemy is on
		Vector2 dir = other->Position() - Position();
		if (dir.x > 0) // enemy on right side
		{
			// Push enemy forward
			other->Position().x += 10;
		}
		else // enemy on left side
		{
			other->Position().x -= 10;
		}
	}

	// If I'm idle and enemy is attacking
	if ((State() != AnimState::Block) && (other->State() == AnimState::Punch || other->State() == AnimState::Kick || other->State() == AnimState::Special))
	{
		SetAnimState(AnimState::Hurt);
		if (other->State() == AnimState::Punch || other->State() == AnimState::Kick)
		{
			mHealth -= 5;
			ResizeHealthBar();
		}
		else if (other->State() == AnimState::Special)
		{
			mHealth -= 10;
			ResizeHealthBar();
		}
	}
}

//----------------------------------------------------------------------------------------------------

void Npc::SetState()
{
	switch(State())
	{
	case AnimState::Idle:
		{
			mVelocity.x = 1.0f;
			Flip(false);
			mDirection = rand() % 2;
			if (mDirection == 1) ChangeDirection();
			SetAnimState(AnimState::Walk);
			break;
		}
	case AnimState::Walk:
		{
			if (OutOfScreen()) { ChangeDirection(); }
			break;
		}
	case AnimState::Punch:
		{
			Velocity() = Vector2();
			if (AnimDone())
			{
				SetActiveCollider(true);
				SetAnimState(AnimState::Idle);
			}
			break;
		}
	case AnimState::Kick:
		{
			Velocity() = Vector2();
			if (AnimDone())
			{
				SetActiveCollider(true);
				SetAnimState(AnimState::Idle);
			}
			break;
		}
	case AnimState::Block:
		{
			Velocity() = Vector2();
			if (AnimDone())
			{
				Animate() = false;
				mElapsedTime += (mTime - mPrevTime) / 1000.0f;
				if (mElapsedTime > 2.0f)
				{
					Animate() = true;
					SetAnimState(AnimState::Idle);
					mElapsedTime = 0;
				}
			}
			break;
		}
	case AnimState::Special:
		{
			Velocity() = Vector2();
			if (AnimDone())
			{
				SetActiveCollider(true);
				SetAnimState(AnimState::Idle);
			}
			break;
		}
	case AnimState::Hurt:
		{
			Velocity() = Vector2();
			SetActiveCollider(false);
			if (AnimDone())
			{
				SetActiveCollider(true);
				SetAnimState(AnimState::Idle);
			}
			break;
		}
	case AnimState::Death:
		{
			Velocity() = Vector2();
			SetActiveCollider(false);
			if (AnimDone())
			{
				Animate() = false;
			}
			break;
		}
	}
}

//----------------------------------------------------------------------------------------------------

bool Npc::OutOfScreen()
{
	if (Position().x < GetWidth() * 0.5f )
	{
		Position().x = GetWidth() * 0.5f;
		return true;
	}
	else if (Position().x > Application::screenWidth - GetWidth() * 0.5f)
	{
		Position().x = Application::screenWidth - GetWidth() * 0.5f;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------

void Npc::ChangeDirection()
{
	mVelocity.x *= -1.0f;
	Flip(!IsFlipped());
}

//----------------------------------------------------------------------------------------------------

void Npc::SetHealthBar(GameObject* hp)
{ 
	mpHealthBar = hp;
	mHPBStartPosX = mpHealthBar->Position().x;
	mHPBStartSizeX = mpHealthBar->GetWidth();
}

//----------------------------------------------------------------------------------------------------

void Npc::ResizeHealthBar()
{
	if (mLeftSide)
	{
		float percent = (float)mHealth / mMaxHealth;
		if (percent < 0)
			percent = 0.0f;
		mpHealthBar->Scale().x = percent;
	
		float offset = mHPBStartSizeX - (mHPBStartSizeX * percent);
		mpHealthBar->Position().x = mHPBStartPosX + offset;
	}
	else
	{
		float percent = (float)mHealth / mMaxHealth;
		if (percent < 0)
			percent = 0.0f;
		mpHealthBar->Scale().x = percent;
		mpHealthBar->Position().x = mHPBStartPosX;
	}
}

//----------------------------------------------------------------------------------------------------

void Npc::UpdateAI()
{
	if (mpTarget && mHard)
	{
		float dist = Math::Distance(Position(), mpTarget->Position());
		if (dist < GetWidth() * 0.5f + mpTarget->GetWidth() * 0.5f &&
			(State() == AnimState::Idle || State() == AnimState::Walk))
		{
			SetRandomState();
		}
	}
	else
	{
		int ran = rand() % Application::screenWidth + 1;
		if ((int)Position().x % ran == 0 &&
			(State() == AnimState::Idle || State() == AnimState::Walk))
		{
			SetRandomState();
		}
	}
}

//----------------------------------------------------------------------------------------------------

void Npc::SetRandomState()
{
	int ranAtk = rand() % 4;
	switch (ranAtk)
	{
	case 0:
		SetAnimState(AnimState::Punch);
		break;
	case 1:
		SetAnimState(AnimState::Kick);
		break;
	case 2:
		SetAnimState(AnimState::Block);
		break;
	case 3:
		SetAnimState(AnimState::Special);
		break;
	}
}

