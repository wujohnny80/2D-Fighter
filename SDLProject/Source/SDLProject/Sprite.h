//====================================================================================================
// Filename:	Sprite.h
// Created by:	Johnny Wu
// Description:	Class for a 2D sprite.
//====================================================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>
#include <map>
#include <vector>

#include "SDL.h"
#include "Texture.h"
#include "Vector2.h"

//====================================================================================================
// Enum
//====================================================================================================

namespace AnimState
{
enum State
{
	None = -1,
	Idle = 0,
	Walk,
	Punch,
	Kick,
	Block,
	Special,
	Hurt,
	Death
};
}

//====================================================================================================
// Struct
//====================================================================================================

struct AnimationInfo
{
	// Assumptions:
	// Each frame has same width, height. An animation is on a single row of an image
	// All animation are on the same image
	// x, y is the top-left position of frame 0

	AnimState::State state;
	int x, y, w, h, frameCount, fps;
};

//====================================================================================================
// Class Declarations
//====================================================================================================

class Sprite
{
	friend class GameObject;
public:
	Sprite();
	~Sprite();

	// Function to update the sprite
	void Update();

	void SetTexture(std::string fileName);

	// Function to get sprite attributes
	float Width() const			{ return (float)mOffset.w; }
	float Height() const		{ return (float)mOffset.h; }
	Vector2 TopLeft()			{ return Vector2((mPosition.x - mAnimations[mAnimState].w * 0.5f), 
												(mPosition.y - mAnimations[mAnimState].h) ); }
	Vector2 Center()			{ return Vector2(mPosition.x, mPosition.y - mAnimations[mAnimState].h * 0.5f); }

private:
	void Render();

	// Animation Helper Functions
	void LoadAnimation(const char* fileName);
	void SetAnimState(AnimState::State state);
	void SetClip(int frame);
	void SetOffset();

	// Texture and sprite related variables
	Texture* mpTexture;
	Vector2 mPosition;
	SDL_Color mColor;
	Vector2 mScale;
	float mWidth;
	float mHeight;
	bool mVisible;	// Render is called when true
	bool mFlipH;	// Flip Horizontal
	
	// Animation related variables
	std::map<AnimState::State, AnimationInfo> mAnimations;
	AnimState::State mAnimState;
	SDL_Rect mClip;
	SDL_Rect mOffset;
	int mFrame;
	bool mAnimDone;
	bool mAnimate;

	// Timer
	float mElapsedTime;
	Uint32 mPrevTime;
	Uint32 mTime;
};

#endif // #ifndef _SPRITE_H_