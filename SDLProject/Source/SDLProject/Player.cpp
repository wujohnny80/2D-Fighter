//====================================================================================================
// Filename:	Player.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Player.h"
#include "Application.h"
#include "InputManager.h"

#include <iostream>

//====================================================================================================
// Macro Defines
//====================================================================================================

#define Input InputManager::Instance()

//====================================================================================================
// Class Definitions
//====================================================================================================

Player::Player(bool leftSide)
	: GameObject()
	, mMaxHealth(100)
	, mLeftSide(leftSide)
{
	mHealth = mMaxHealth;

	Position().y = 700;
	if (mLeftSide)
		Position().x = 200;
	else
		Position().x = 1080;
}

//----------------------------------------------------------------------------------------------------

void Player::Update()
{
	HandleOutOfScreen();
	
	if (mHealth <= 0 && State() != AnimState::Death)
	{
		SetAnimState(AnimState::Death);
	}
	
	Position().x += mVelocity.x * mSpeed;
	if (mLeftSide)
		SetStatePlayer1();
	else
		SetStatePlayer2();

	// Update Sprite
	mpSprite->Update();

	// Update Collider
	UpdateCollider();
}

//----------------------------------------------------------------------------------------------------

void Player::HandleCollision(GameObject* other)
{
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

void Player::SetStatePlayer1()
{
	switch(State())
	{
	case AnimState::Idle:
		{
			Velocity() = Vector2();
			// Walk with "wasd"
			if (Input.KeyDown(Keys::A) || Input.KeyDown(Keys::D))
				SetAnimState(AnimState::Walk);
			// Block with space
			if (Input.KeyDown(Keys::S))
				SetAnimState(AnimState::Block);
			// Punch with LMouse
			if (Input.KeyDown(Keys::G))
				SetAnimState(AnimState::Punch);
			// Kick with RMouse
			if (Input.KeyDown(Keys::H))
				SetAnimState(AnimState::Kick);
			// Special with RMouse while holding left shift
			if (Input.KeyDown(Keys::J))
				SetAnimState(AnimState::Special);
			break;
		}
	case AnimState::Walk:
		{
			if (!(Input.KeyDown(Keys::A) || Input.KeyDown(Keys::D)))
				SetAnimState(AnimState::Idle);
			// Move around
			if (Input.KeyDown(Keys::D))
			{
				Flip(false);
				Velocity().x = 1.0f;
				Speed() = 5.0f;
			}
			if (Input.KeyDown(Keys::A))
			{
				Flip(true);
				Velocity().x = -1.0f;
				Speed() = 5.0f;
			}
			// Block with space
			if (Input.KeyDown(Keys::S))
				SetAnimState(AnimState::Block);
			// Punch with LMouse
			if (Input.KeyDown(Keys::G))
				SetAnimState(AnimState::Punch);
			// Kick with RMouse
			if (Input.KeyDown(Keys::H))
				SetAnimState(AnimState::Kick);
			// Special with RMouse while holding left shift
			if (Input.KeyDown(Keys::J))
				SetAnimState(AnimState::Special);
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
			}
			if (!Input.KeyDown(Keys::S))
			{
				Animate() = true;
				SetAnimState(AnimState::Idle);
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
	default:
		break;
	}
}

//----------------------------------------------------------------------------------------------------

void Player::SetStatePlayer2()
{
	switch(State())
	{
	case AnimState::Idle:
		{
			Velocity() = Vector2();
			// Walk with arrow keys
			if (Input.KeyDown(Keys::LEFT) || Input.KeyDown(Keys::RIGHT))
				SetAnimState(AnimState::Walk);
			// Block with Right ctrl
			if (Input.KeyDown(Keys::DOWN))
				SetAnimState(AnimState::Block);
			// Punch with num1
			if (Input.KeyDown(Keys::KP_1))
				SetAnimState(AnimState::Punch);
			// Kick with num2
			if (Input.KeyDown(Keys::KP_2))
				SetAnimState(AnimState::Kick);
			// Special with num3
			if (Input.KeyDown(Keys::KP_3))
				SetAnimState(AnimState::Special);
			break;
		}
	case AnimState::Walk:
		{
			if (!(Input.KeyDown(Keys::LEFT) || Input.KeyDown(Keys::RIGHT)))
				SetAnimState(AnimState::Idle);
			// Move around
			if (Input.KeyDown(Keys::RIGHT))
			{
				Flip(false);
				Velocity().x = 1.0f;
				Speed() = 5.0f;
			}
			if (Input.KeyDown(Keys::LEFT))
			{
				Flip(true);
				Velocity().x = -1.0f;
				Speed() = 5.0f;
			}
			// Block with Right ctrl
			if (Input.KeyDown(Keys::DOWN))
				SetAnimState(AnimState::Block);
			// Punch with num1
			if (Input.KeyDown(Keys::KP_1))
				SetAnimState(AnimState::Punch);
			// Kick with num2
			if (Input.KeyDown(Keys::KP_2))
				SetAnimState(AnimState::Kick);
			// Special with num3
			if (Input.KeyDown(Keys::KP_3))
				SetAnimState(AnimState::Special);
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
			}
			if (!Input.KeyDown(Keys::DOWN))
			{
				Animate() = true;
				SetAnimState(AnimState::Idle);
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
	default:
		break;
	}
}

//----------------------------------------------------------------------------------------------------

void Player::HandleOutOfScreen()
{
	if (Position().x < GetWidth() * 0.5f )
	{
		Position().x = GetWidth() * 0.5f;
	}
	else if (Position().x > Application::screenWidth - GetWidth() * 0.5f)
	{
		Position().x = Application::screenWidth - GetWidth() * 0.5f;
	}
}

//----------------------------------------------------------------------------------------------------

void Player::SetHealthBar(GameObject* hp)
{ 
	mpHealthBar = hp;
	mHPBStartPosX = mpHealthBar->Position().x;
	mHPBStartSizeX = mpHealthBar->GetWidth();
}

//----------------------------------------------------------------------------------------------------

void Player::ResizeHealthBar()
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