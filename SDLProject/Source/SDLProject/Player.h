//====================================================================================================
// Filename:	Player.h
// Created by:	Johnny Wu
// Description:	Class for a Player
//====================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>

#include "GameObject.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Player : public GameObject
{
public:
	Player(bool leftSide);

	void Update();
	void HandleCollision(GameObject* other);
	void SetHealthBar(GameObject* hp);
	int& Health()							{ return mHealth; }
	bool LeftSide()	const					{ return mLeftSide; }

private:
	void SetStatePlayer1();
	void SetStatePlayer2();
	void HandleOutOfScreen();
	void ResizeHealthBar();
	
	GameObject* mpHealthBar;
	float mHPBStartPosX;
	float mHPBStartSizeX;
	const int mMaxHealth;
	int mHealth;
	int mLeftSide;
};

#endif // #ifndef _PLAYER_H_