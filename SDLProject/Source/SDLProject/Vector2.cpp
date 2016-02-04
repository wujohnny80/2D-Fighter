//====================================================================================================
// Filename:	Vector2.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Vector2.h"

#include <stdio.h>

bool Vector2::operator==(const Vector2& rhs) const
{
	if ((x == rhs.x) && (y == rhs.y))
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------

bool Vector2::operator!=(const Vector2& rhs) const
{
	if ((x != rhs.x) || (y != rhs.y))
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

//----------------------------------------------------------------------------------------------------

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

//----------------------------------------------------------------------------------------------------

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

//----------------------------------------------------------------------------------------------------

Vector2 Vector2::operator*(float s) const
{
	return Vector2(x * s, y * s);
}

//----------------------------------------------------------------------------------------------------

Vector2 operator*(float s, const Vector2& v)
{
	return v * s;
}

//----------------------------------------------------------------------------------------------------

Vector2 Vector2::operator/(float s) const
{
	if (s == 0)
		printf("Cannot divide by zero");
	const float inv = 1.0f / s;
	return Vector2(x * inv, y * inv);
}

//----------------------------------------------------------------------------------------------------

Vector2 operator/(float s, const Vector2& v)
{
	return v / s;
}