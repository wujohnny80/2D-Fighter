//====================================================================================================
// Filename:	Vector2.h
// Created by:	Johnny Wu
// Description:	Struct for a 2D vector.
//====================================================================================================
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <math.h>

struct Vector2
{
	float x, y;

	Vector2() 
		: x(0.0f)
		, y(0.0f)
	{}
	Vector2(const Vector2& rhs)
		: x(rhs.x)
		, y(rhs.y)
	{}
	Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;
	Vector2 operator-() const;
	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator*(float s) const;
	friend Vector2 operator*(float s, const Vector2& v);
	Vector2 operator/(float s) const;
	friend Vector2 operator/(float s, const Vector2& v);

	float MagnitudeSqr() const	{ return (x * x) + (y * y); } 
	float Magnitude() const		{ return sqrt(MagnitudeSqr()); }
};

#endif // #ifndef _VECTOR2_H_