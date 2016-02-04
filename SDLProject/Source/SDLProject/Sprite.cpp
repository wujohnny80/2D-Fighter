//====================================================================================================
// Filename:	Sprite.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Sprite.h"

#include <assert.h>
#include <iostream>
#include <fstream>

#include "GraphicSystem.h"
#include "ResourceManager.h"
#include "SDL.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Sprite::Sprite()
	: mpTexture(nullptr)
	, mPosition(0.0f, 0.0f)
	, mScale(1.0f, 1.0f)
	, mWidth(0.0f)
	, mHeight(0.0f)
	, mVisible(true)
	, mFlipH(false)
	, mAnimState(AnimState::None)
	, mFrame(0)
	, mAnimDone(false)
	, mAnimate(false)
	, mElapsedTime(0)
	, mPrevTime(0)
	, mTime(0)
{

	mColor.r = 255;
	mColor.g = 255;
	mColor.b = 255;
	mColor.a = 255;

	mOffset.x = 0;
	mOffset.y = 0;
	mOffset.w = 0;
	mOffset.h = 0;

	mClip.x = 0;
	mClip.y = 0;
	mClip.w = 0;
	mClip.h = 0;
}

//----------------------------------------------------------------------------------------------------

Sprite::~Sprite()
{
}

//----------------------------------------------------------------------------------------------------

void Sprite::Update()
{
	// Update any animation
	mTime = SDL_GetTicks(); // Gives time in milliseconds
	mElapsedTime += (mTime - mPrevTime) / 1000.0f;

	if (mVisible)
	{
		SetOffset();
		if (mAnimate)
		{
			SetClip(mFrame);
			if (mElapsedTime > 1.0f / mAnimations[mAnimState].fps)
			{
				mFrame++;
				mElapsedTime = 0.0f;

				// Reached last frame, loop back
				if (mFrame >= mAnimations[mAnimState].frameCount)
				{
 					mFrame = 0;
					mAnimDone = true;
				}
			}
		}
		Render();
	}

	mPrevTime = mTime;
}

//----------------------------------------------------------------------------------------------------

void Sprite::Render()
{
	// Check if we have a valid texture
	if (mpTexture == nullptr)
	{
		return;
	}

	SDL_Renderer* renderer = GraphicSystem::Instance().GetRenderer();

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (mFlipH)
		flip = SDL_FLIP_HORIZONTAL;

	mpTexture->Render(renderer, &mClip, &mOffset, mColor, flip);
}

//----------------------------------------------------------------------------------------------------

void Sprite::SetTexture(std::string fileName)
{
	mpTexture = ResourceManager::Instance().GetTexture(fileName);
	mWidth = mpTexture->Width();
	mHeight = mpTexture->Height();

	mOffset.w = (int)mWidth;
	mOffset.h = (int)mHeight;
	mClip.w = (int)mWidth;
	mClip.h = (int)mHeight;
}

//----------------------------------------------------------------------------------------------------

void Sprite::LoadAnimation(const char* fileName)
{
	// Construct full path name
	std::string fullPath = "../../Assets/Animations/";
	fullPath += fileName;

	// Open the file
	std::ifstream file;
	file.open(fullPath);

	// Check if the file is openend properly
	if (file.fail())
	{
		std::cout << "Failed to open file\n";
		return;
	}

	// Read/Write
	std::string temp, imgfile, name;
	int x, y, w, h, numframes, fps;

	if (file.peek() == '#')
		getline(file, temp);

	file >> temp >> imgfile;
	SetTexture(imgfile);

	while (!file.eof())
	{
		if(file.peek() == '#' || file.peek() == 10)
		{
			getline(file, temp);
			continue;
		}
		file >> temp >> name >> x >> y >> w >> h >> numframes >> fps;

		AnimState::State s = AnimState::None;
		if (name == "Idle")
			s = AnimState::Idle;
		else if (name == "Walk")
			s = AnimState::Walk;
		else if (name == "Punch")
			s = AnimState::Punch;
		else if (name == "Kick")
			s = AnimState::Kick;
		else if (name == "Block")
			s = AnimState::Block;
		else if (name == "Special")
			s = AnimState::Special;
		else if (name == "Hurt")
			s = AnimState::Hurt;
		else if (name == "Death")
			s = AnimState::Death;

		mAnimations[s].state = s;
		mAnimations[s].x = x;
		mAnimations[s].y = y;
		mAnimations[s].w = w;
		mAnimations[s].h = h;
		mAnimations[s].frameCount = numframes;
		mAnimations[s].fps = fps;

		getline(file, temp);
	}

	mAnimate = true;
	mAnimState = AnimState::Idle;
	SetOffset();
	SetClip(mFrame);

	// We are done with the file
	file.close();
}

//----------------------------------------------------------------------------------------------------

void Sprite::SetAnimState(AnimState::State state)		
{
	mAnimState = state;
	mFrame = 0;
	mElapsedTime = 0.0f;
	mAnimDone = false;
}

//----------------------------------------------------------------------------------------------------

void Sprite::SetClip(int frame)
{
	mClip.x = mAnimations[mAnimState].x + mFrame * mAnimations[mAnimState].w;
	mClip.y = mAnimations[mAnimState].y;
	mClip.w = mAnimations[mAnimState].w;
	mClip.h = mAnimations[mAnimState].h;
}

//----------------------------------------------------------------------------------------------------

void Sprite::SetOffset()
{
	if (mAnimState == AnimState::None)
	{
		mOffset.w = (int)(mWidth * mScale.x);
		mOffset.h = (int)(mHeight * mScale.y);
		mOffset.x = mPosition.x;
		mOffset.y = mPosition.y;
	}
	else
	{
		mOffset.x = (mPosition.x - mAnimations[mAnimState].w * 0.5f * mScale.x);
		mOffset.y = (mPosition.y - mAnimations[mAnimState].h * mScale.y);
		mOffset.w = mAnimations[mAnimState].w * mScale.x;
		mOffset.h = mAnimations[mAnimState].h * mScale.y;
	}
}