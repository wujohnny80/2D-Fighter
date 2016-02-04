//====================================================================================================
// Filename:	GameManager.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "GameManager.h"

#include "AABBCollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

GameManager::GameManager()
{
	mpPlayer1 = nullptr;
	mpPlayer2 = nullptr;
	mpNpc1 = nullptr;
	mpNpc2 = nullptr;
	mpHPBar1 = nullptr;
	mpHPBar2 = nullptr;
}

//----------------------------------------------------------------------------------------------------

GameManager::~GameManager()
{
}

//----------------------------------------------------------------------------------------------------

void GameManager::InitGame()
{
	LoadAgents("Level1.txt");
}

//----------------------------------------------------------------------------------------------------

void GameManager::RunGame()
{	
	// Insert into render queue
	for(unsigned int i = 0; i < mpObjects.size(); ++i)
	{
		GameObjectNode node = { mpObjects[i] };
		mRenderQueue.Insert(node);
	}
	for(int i = 0; i < mRenderQueue.Size(); ++i)
	{
		mRenderQueue.Remove().obj->Update();
	}
}

//----------------------------------------------------------------------------------------------------

void GameManager::StopGame()
{
	// Do Clean-up
	for(unsigned int i = 0; i < mpObjects.size(); ++i)
	{
		delete mpObjects[i];
		mpObjects[i] = nullptr;
	}
}

//----------------------------------------------------------------------------------------------------

void GameManager::LoadAgents(const char* fileName)
{
	std::ifstream file;
	if(!InitFile(file, fileName))
		return;

	// Read/Write
	std::string type, name, animFile, difficulty;
	int x, y, flip, layer;
	float scale;

	while (!file.eof())
	{
		if(file.peek() == '#' || file.peek() == 10)
		{
			getline(file, type);
			continue;
		}

		file >> type >> name >> x >> y >> scale >> flip >> layer >> difficulty >> animFile;

		GameObject* temp = nullptr;
		if(type == "player1")
		{
			mpPlayer1 = new Player(true);
			mpPlayer1->Name() = name.c_str();
			//mpPlayer1->Position() = Vector2((float)x, (float)y);
			mpPlayer1->Scale() = Vector2(scale, scale);
			mpPlayer1->Flip(flip);
			mpPlayer1->Layer() = layer;
			mpPlayer1->SetAnimation(animFile.c_str(), AnimState::Idle);
			mpPlayer1->AddCollider(ColliderTypes::Circle);
			temp = mpPlayer1;
		}
		if(type == "player2")
		{
			mpPlayer2 = new Player(false);
			mpPlayer2->Name() = name.c_str();
			//mpPlayer2->Position() = Vector2((float)x, (float)y);
			mpPlayer2->Scale() = Vector2(scale, scale);
			mpPlayer2->Flip(flip);
			mpPlayer2->Layer() = layer;
			mpPlayer2->SetAnimation(animFile.c_str(), AnimState::Idle);
			mpPlayer2->AddCollider(ColliderTypes::Circle);
			temp = mpPlayer2;
		}
		else if (type == "npc1")
		{
			mpNpc1 = new Npc(true);
			mpNpc1->Name() = name.c_str();
			//mpNpc1->Position() = Vector2((float)x, (float)y);
			mpNpc1->Scale() = Vector2(scale, scale);
			mpNpc1->Flip(flip);
			mpNpc1->Layer() = layer;
			mpNpc1->SetAnimation(animFile.c_str(), AnimState::Idle);
			mpNpc1->AddCollider(ColliderTypes::Circle);
			if (difficulty == "hard")				
				mpNpc1->IsHard() = true;
			temp = mpNpc1;
		}
		else if (type == "npc2")
		{
			mpNpc2 = new Npc(false);
			mpNpc2->Name() = name.c_str();
			//mpNpc2->Position() = Vector2((float)x, (float)y);
			mpNpc2->Scale() = Vector2(scale, scale);
			mpNpc2->Flip(flip);
			mpNpc2->Layer() = layer;
			mpNpc2->SetAnimation(animFile.c_str(), AnimState::Idle);
			mpNpc2->AddCollider(ColliderTypes::Circle);
			if (difficulty == "hard")				
				mpNpc2->IsHard() = true;
			temp = mpNpc2;
		}
		else if (type == "bg")
		{
			GameObject* newObj = new GameObject();
			newObj->Name() = name.c_str();
			newObj->Position() = Vector2((float)x, (float)y);
			newObj->Scale() = Vector2(scale, scale);
			newObj->Flip(flip);
			newObj->Layer() = layer;
			newObj->SetSprite(animFile.c_str());
			temp = newObj;
		}
		else if (type == "hp1")
		{
			mpHPBar1 = new GameObject();
			mpHPBar1->Name() = name.c_str();
			mpHPBar1->Position() = Vector2((float)x, (float)y);
			mpHPBar1->Scale() = Vector2(scale, scale);
			mpHPBar1->Flip(flip);
			mpHPBar1->Layer() = layer;
			mpHPBar1->SetSprite(animFile.c_str());
			temp = mpHPBar1;
		}
		else if (type == "hp2")
		{
			mpHPBar2 = new GameObject();
			mpHPBar2->Name() = name.c_str();
			mpHPBar2->Position() = Vector2((float)x, (float)y);
			mpHPBar2->Scale() = Vector2(scale, scale);
			mpHPBar2->Flip(flip);
			mpHPBar2->Layer() = layer;
			mpHPBar2->SetSprite(animFile.c_str());
			temp = mpHPBar2;
		}
		mpObjects.push_back(temp);
		getline(file, type);
	}

	// Set hpbar for player1
	if (mpPlayer1 && mpPlayer1->LeftSide())
		mpPlayer1->SetHealthBar(mpHPBar1);
	else if (mpPlayer1 && !mpPlayer1->LeftSide())
		mpPlayer1->SetHealthBar(mpHPBar2);
	
	// Set hpbar for player2
	if (mpPlayer2 && mpPlayer2->LeftSide())
		mpPlayer2->SetHealthBar(mpHPBar1);
	else if (mpPlayer2 && !mpPlayer2->LeftSide())
		mpPlayer2->SetHealthBar(mpHPBar2);
	
	// Set hpbar for npc1
	if (mpNpc1 && mpNpc1->LeftSide())
		mpNpc1->SetHealthBar(mpHPBar1);
	else if (mpNpc1 && !mpNpc1->LeftSide())
		mpNpc1->SetHealthBar(mpHPBar2);
	
	// Set hpbar for npc2
	if (mpNpc2 && mpNpc2->LeftSide())
		mpNpc2->SetHealthBar(mpHPBar1);
	else if (mpNpc2 && !mpNpc2->LeftSide())
		mpNpc2->SetHealthBar(mpHPBar2);

	// We are done with the file
	file.close();
}

//----------------------------------------------------------------------------------------------------

bool GameManager::InitFile(std::ifstream& file, const char* fileName)
{
	// Construct full path name
	std::string fullPath = "../../Assets/Scenes/";	// Up two folder from project dir -> Asset -> Scenes
	fullPath += fileName;

	// Open the file
	file.open(fullPath);

	// Check if the file is openend properly
	if (file.fail())
	{
		std::cout << "Failed to open file\n";
		return false;
	}

	return true;
}