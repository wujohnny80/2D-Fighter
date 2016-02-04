//====================================================================================================
// Filename:	GameManager.h
// Created by:	Johnny Wu
// Description:	Class for a game manager.
//====================================================================================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <fstream>
#include <iostream>
#include <vector>

#include "Application.h"
#include "Heap.h"
#include "Npc.h"
#include "Player.h"

//====================================================================================================
// Struct
//====================================================================================================

struct GameObjectNode
{
	GameObject* obj;
	bool operator<(const GameObjectNode& other)
	{
		return obj->Layer() < other.obj->Layer();
	}
};

//====================================================================================================
// Class Declarations
//====================================================================================================

class GameManager : public Application
{
public:
	GameManager();
	~GameManager();

protected:
	// Game related user defined logics
	virtual void InitGame();
	virtual void RunGame();
	virtual void StopGame();

private:
	void LoadAgents(const char* fileName);
	void LoadEnvironment(const char* fileName);
	bool InitFile(std::ifstream& file, const char* fileName);
	
	Heap<GameObjectNode> mRenderQueue;
	std::vector<GameObject*> mpObjects;

	Player* mpPlayer1;
	Player* mpPlayer2;
	Npc* mpNpc1;
	Npc* mpNpc2;
	GameObject* mpHPBar1;
	GameObject* mpHPBar2;
};

#endif // #ifndef _GAMEMANAGER_H_