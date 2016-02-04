//====================================================================================================
// Filename:	CollisionSystem.h
// Created by:	Johnny Wu
// Description:	Singleton class for collision system.
//====================================================================================================
#ifndef _COLLISIONSYSTEM_H_
#define _COLLISIONSYSTEM_H_

#include <vector>

#include "Application.h"
#include "Collider.h"
#include "QuadTree.h"
//====================================================================================================
// Class Declarations
//====================================================================================================

class CollisionSystem
{
	friend class Application;
public:
	static CollisionSystem& Instance()	{ static CollisionSystem instance; return instance; }
	
	void AddColliders(Collider* collider);
	void RemoveCollider(Collider* collider);

	void OnCollisionEnter();
	void OnCollisionStay();

private:
	CollisionSystem();
	CollisionSystem(CollisionSystem const&);	// Don't implement
	void operator=(CollisionSystem const&);		// Don't implement

	void Initialize(int winWidth, int winHeight);
	void Update();
	void Terminate();

	QuadTree mQuadTree;
	std::vector<Collider*> mColliders;

	bool mInitialized;							// Init flag
};

#endif // #ifndef _CollisionSystem_H_