//====================================================================================================
// Filename:	Collider.h
// Created by:	Johnny Wu
// Description:	Base class for 2D colliders
//====================================================================================================
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <map>
#include <typeinfo>
#include <string>

#include "Vector2.h"

//====================================================================================================
// Enum
//====================================================================================================
namespace ColliderTypes
{
enum Type
{
	AABB,
	Box,
	Circle
};
}

//====================================================================================================
// Forward Declarations
//====================================================================================================
class Collider;
class GameObject;

//====================================================================================================
// Typedef
//====================================================================================================
typedef bool (*CollisionFunctor)(Collider*, Collider*);

//====================================================================================================
// Class Declarations
//====================================================================================================

class Collider
{
public:
	Collider(GameObject* const owner);
	virtual ~Collider();
	
	virtual void Update();
	bool IsColliding(Collider* other);
	
	bool IsActive()	const		{ return mActive; }
	void SetActive(bool b)		{ mActive = b; }
	GameObject* Owner()			{ return mpOwner; }
	Vector2& Offset()			{ return mOffset; }
	Vector2 PositionTL();
	Vector2 PositionCenter();
	Vector2 CurrentSize();

protected:
	std::map<std::string, CollisionFunctor> mFunctors;
	GameObject* const mpOwner;
	Vector2 mOffset;
	bool mActive;
};

#endif // #ifndef _COLLIDER_H_