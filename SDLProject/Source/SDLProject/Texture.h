//====================================================================================================
// Filename:	Texture.h
// Created by:	Johnny Wu
// Description:	Wrapper class for a SDL_Texture
//====================================================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "SDL.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Texture
{
public:
	Texture();
	~Texture();

	void Load(const char* fileName);
	void Render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* offset, SDL_Color color, SDL_RendererFlip flip);

	float Width() const	{ return (float)mWidth; }
	float Height() const	{ return (float)mHeight; }

private:
	SDL_Texture* mpTexture;
	int mWidth;
	int mHeight;
};

#endif // #ifndef _TEXTURE_H_