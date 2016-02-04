//====================================================================================================
// Filename:	Line.h
// Created by:	Johnny Wu
// Description:	Struct for a 2D line.
//====================================================================================================
#ifndef _LINE_H_
#define _LINE_H_

#include "Vector2.h"

struct Line
{
	Vector2 from, to;

	Line()
		: from(0.0f, 0.0f)
		, to(0.0f, 0.0f)
	{}

	Line(const Vector2& v0, const Vector2& v1)
		: from(v0)
		, to(v1)
	{}

	Line(float x0, float y0, float x1, float y1)
		: from(x0, y0)
		, to(x1, y1)
	{}
};

#endif // #ifndef _LINE_H_