//====================================================================================================
// Filename:	GameObject.h
// Created by:	Johnny Wu
// Description:	Class for a GameObject.
//====================================================================================================
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <string>

#include "AABBCollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Collider.h"
#include "Sprite.h"
#include "Vector2.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update();
	void Destroy();
	virtual void HandleCollision(GameObject* other);

	void AddCollider(ColliderTypes::Type type);
	void SetSprite(const char* fileName);
	void SetAnimation(const char* fileName, AnimState::State state = AnimState::None);
	void SetActiveCollider(bool active);
	void UpdateCollider();
	void SetAnimState(AnimState::State state)	{ mpSprite->SetAnimState(state); }
	bool AnimDone() const						{ return mpSprite->mAnimDone; }
	void Flip(bool flip)						{ mpSprite->mFlipH = flip; }
	bool IsFlipped() const						{ return mpSprite->mFlipH; }

	// Accessor
	Sprite* GetSprite() const			{ return mpSprite; }
	int CurrentFrame() const			{ return mpSprite->mFrame; }
	int GetAnimFrames()					{ return mpSprite->mAnimations[State()].frameCount; }
	int GetAnimFPS()					{ return mpSprite->mAnimations[State()].fps; }
	float GetWidth() const				{ return mpSprite->Width(); }
	float GetHeight() const				{ return mpSprite->Height(); }

	// References
	Vector2& Position() 				{ return mpSprite->mPosition; }
	Vector2& Scale()					{ return mpSprite->mScale; }
	SDL_Color& Color()					{ return mpSprite->mColor; }
	int& Layer()						{ return mLayer; }	
	std::string& Name()					{ return mName; }
	Vector2& Velocity()					{ return mVelocity; }
	float& Speed()						{ return mSpeed; }
	AnimState::State State()			{ return mpSprite->mAnimState; }
	bool& Animate()						{ return mpSprite->mAnimate; }

protected:
	Sprite* mpSprite;
	int mLayer;
	std::string mName;
	Vector2 mVelocity;
	float mSpeed;

private:	
	// Colliders
	AABBCollider* mpAABBCol;
	BoxCollider* mpBoxCol;
	CircleCollider* mpCircleCol;
};

#endif // #ifndef _GAMEOBJECT_H_