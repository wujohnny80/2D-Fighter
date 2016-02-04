//====================================================================================================
// Filename:	HealthBar.h
// Created by:	Johnny Wu
// Description:	Class for a HealthBar
//====================================================================================================
#ifndef _HEALTHBAR_H_
#define _HEALTHBAR_H_

#include <string>

#include "GameObject.h"
#include "Player.h"
#include "Npc.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class HealthBar : public GameObject
{
public:
	HealthBar();

	void Update();

private:
	Player* mPlayer;
	Npc* mNpc;
};

#endif // #ifndef _HEALTHBAR_H_