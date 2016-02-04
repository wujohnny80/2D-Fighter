//====================================================================================================
// Filename:	InputManager.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "InputManager.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

InputManager::InputManager()
	: mMousePosition(Vector2())
	, mAnyKeyPressed(false)
	, mInitialized(false)
{
}

//----------------------------------------------------------------------------------------------------

void InputManager::Initialize()
{	
	// Set flag
	mInitialized = true;
}


//----------------------------------------------------------------------------------------------------

void InputManager::Update()
{
	// Loop through currentKeyState and copy it over to prevKeyState
	auto it = mCurrentKeyState.begin();
	for (; it != mCurrentKeyState.end(); ++it)
	{
		mPrevKeyState[it->first] = it->second;
	}
}

//----------------------------------------------------------------------------------------------------

void InputManager::Terminate()
{
	// Set flag
	mInitialized = false;
}

//----------------------------------------------------------------------------------------------------

void InputManager::PressKey(int key)
{
	mAnyKeyPressed = true;
	mCurrentKeyState[key] = true;
}

//----------------------------------------------------------------------------------------------------

void InputManager::ReleaseKey(int key)
{
	mAnyKeyPressed = false;
	mCurrentKeyState[key] = false;
}

//----------------------------------------------------------------------------------------------------

bool InputManager::KeyDown(int key)
{
	return mCurrentKeyState[key];
}

//----------------------------------------------------------------------------------------------------

bool InputManager::KeyPressed(int key)
{
	// Check if it is pressed this frame, and isn't pressed last frame
	if (KeyDown(key) && !WasKeyDown(key)) 
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------

void InputManager::SetMouse(int x, int y)
{
	mMousePosition.x = (float)x;
	mMousePosition.y = (float)y;
}

//----------------------------------------------------------------------------------------------------

bool InputManager::WasKeyDown(int key)
{
	// Don't create a key if it doesnt exist.
	auto it = mPrevKeyState.find(key);
	if (it != mPrevKeyState.end()) 
	{
		return it->second;
	}
	else 
	{
		// Didn't find the key
		return false;
	}
}