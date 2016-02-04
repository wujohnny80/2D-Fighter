//====================================================================================================
// Filename:	InputManager.h
// Created by:	Johnny Wu
// Description:	Class for the input system.
//====================================================================================================
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <unordered_map>

#include "Application.h"
#include "InputTypes.h"
#include "Vector2.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class InputManager
{
	friend class Application;
public:
	static InputManager& Instance()	{ static InputManager instance; return instance; }
	
	bool AnyKeyPressed() const		{ return mAnyKeyPressed; }

	// Functions to query for a key state
	bool KeyDown(int key);
	bool KeyPressed(int key);
	
	// Functions to query for a mouse state
	bool MouseDown();
	bool MousePressed();
	Vector2 MousePosition() const		{ return mMousePosition; }

private:
	InputManager();
	InputManager(InputManager const&);		// Don't implement
	void operator=(InputManager const&);	// Don't implement

	void Initialize();
	void Update();
	void Terminate();

	void PressKey(int key);
	void ReleaseKey(int key);
	bool WasKeyDown(int key);
	
	void SetMouse(int x, int y);

	std::unordered_map<int, bool> mCurrentKeyState;
	std::unordered_map<int, bool> mPrevKeyState;

	Vector2 mMousePosition;

	bool mAnyKeyPressed;
	bool mInitialized;						// Init flag
};

#endif // #ifndef _INPUTMANAGER_H_