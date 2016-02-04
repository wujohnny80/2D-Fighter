//====================================================================================================
// Filename:	Math.h
// Created by:	Johnny Wu
// Description:	Math library header.
//====================================================================================================
#ifndef _MATH_H_
#define _MATH_H_

#ifdef max
	#undef max
#endif

#ifdef min
	#undef min
#endif

//====================================================================================================
// Includes
//====================================================================================================
#include <float.h>
#include <math.h>
#include <stdio.h>

#include "Circle.h"
#include "Line.h"
#include "Rect.h"
#include "Vector2.h"

//====================================================================================================
// Namespace
//====================================================================================================

namespace Math
{

//====================================================================================================
// Constants
//====================================================================================================

const float Epsilon		= 0.000001f;
const float Pi			= 3.14159265358979f;

//====================================================================================================
// Function Declarations
//====================================================================================================

inline int Min(int a, int b)			{ return (a > b) ? b : a; }
inline float Min(float a, float b)		{ return (a > b) ? b : a; }

inline int Max(int a, int b)			{ return (a < b) ? b : a; }
inline float Max(float a, float b)		{ return (a < b) ? b : a; }

inline int Clamp(int value, int min, int max)			{ return Max(min, Min(max, value)); }
inline float Clamp(float value, float min, float max)	{ return Max(min, Min(max, value)); }

inline float Abs(float value)	{ return (value >= 0.0f) ? value : -value; }
inline float Sgn(float value)	{ return (value >= 0.0f) ? 1.0f : -1.0f; }
inline float Sqr(float value)	{ return value * value; }

inline Vector2 Normalize(const Vector2& v)
{
	if (v == Vector2())
		printf("Cannot normalize zero length vector");
	const float inv = 1.0f / v.Magnitude();
	return Vector2(v.x * inv, v.y * inv);
}

inline float DistanceSqr(const Vector2& a, const Vector2& b)
{
	const float diffX = a.x - b.x;
	const float diffY = a.y - b.y;
	return (diffX * diffX) + (diffY * diffY);
}

inline float Distance(const Vector2& a, const Vector2& b)	{ return sqrt(DistanceSqr(a, b)); }
inline float Dot(const Vector2& a, const Vector2& b)		{ return (a.x * b.x) + (a.y * b.y); }
inline Vector2 Project(const Vector2& v, const Vector2 &n)	{ return v * (Dot(v, n) / Dot(n, n)); }

inline float DegToRad(float degree)	{ return degree * Pi / 180.0f; }
inline float RadToDeg(float radian)	{ return radian * 180.0f / Pi; }

// Function to check if a point is inside a rectangle
bool PointInRect(const Vector2& point, const Rect& rect);
bool PointInCircle(const Vector2& point, const Circle& circle);

// Functions for intersect tests between different shapes
bool Intersect(const Line& a, const Line& b);
bool Intersect(const Circle& c0, const Circle& c1);
bool Intersect(const Rect& r0, const Rect& r1);

bool Intersect(const Line& l, const Circle& c);
bool Intersect(const Circle& c, const Line& l);

bool Intersect(const Circle& c, const Rect& r);
bool Intersect(const Rect& r, const Circle& c);

} // namespace Math

#endif // #ifndef _MATH_H_