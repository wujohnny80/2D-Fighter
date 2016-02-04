//====================================================================================================
// Filename:	Npc.h
// Created by:	Johnny Wu
// Description:	Class for a Npc
//====================================================================================================
#ifndef _NPC_H_
#define _NPC_H_

#include <string>

#include "GameObject.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Npc : public GameObject
{
public:
	Npc(bool leftSide);

	void Update();
	void HandleCollision(GameObject* other);
	void SetHealthBar(GameObject* hp);
	int& Health()							{ return mHealth; }
	bool& IsHard()							{ return mHard; }
	bool LeftSide()	const					{ return mLeftSide; }

private:
	void SetState();
	void ResizeHealthBar();
	
	// AI
	bool OutOfScreen();
	void ChangeDirection();
	void UpdateAI();
	void SetRandomState();	
	GameObject* mpTarget;
	int mDirection;
	bool mHard;

	// GUI
	GameObject* mpHealthBar;
	float mHPBStartPosX;
	float mHPBStartSizeX;
	const int mMaxHealth;
	int mHealth;
	int mLeftSide;

	// Timer
	float mElapsedTime;
	float mTime;
	float mPrevTime;
};

#endif // #ifndef _NPC_H_