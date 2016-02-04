//====================================================================================================
// Filename:	Circle.h
// Created by:	Johnny Wu
// Description:	Struct for a 2D circle.
//====================================================================================================
#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Vector2.h"

struct Circle
{
	Vector2 center;
	float radius;

	Circle()
		: center(0.0f, 0.0f)
		, radius(0.0f)
	{}

	Circle(float x, float y, float r)
		: center(x, y)
		, radius(r)
	{}

	Circle(const Vector2& v, float r)
		: center(v)
		, radius(r)
	{}
};

#endif // #ifndef _CIRCLE_H_