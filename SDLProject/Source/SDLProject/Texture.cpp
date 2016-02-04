//====================================================================================================
// Filename:	Texture.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Texture.h"

#include <assert.h>
#include <stdio.h>
#include <string>

#include "GraphicSystem.h"
#include "ImageLoader.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Texture::Texture()
	: mpTexture(nullptr)
	, mWidth(0)
	, mHeight(0)
{
}

//----------------------------------------------------------------------------------------------------

Texture::~Texture()
{
	SDL_DestroyTexture(mpTexture);
}

//----------------------------------------------------------------------------------------------------

void Texture::Load(const char* fileName)
{
	// Construct full path name
	std::string fullPath = "../../Assets/Images/";	// Up two folder from project dir -> Asset -> Images
	fullPath += fileName;

	//Load the texture
	mpTexture = ImageLoader::Load(fullPath.c_str());

	// Get texture dimension
	if (mpTexture != nullptr)
	{
		SDL_QueryTexture(mpTexture, 0, 0, &mWidth, &mHeight);
	}
}

//----------------------------------------------------------------------------------------------------

void Texture::Render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* offset, SDL_Color color, SDL_RendererFlip flip)
{
	// Check if we have a valid texture
	if (mpTexture == nullptr)
	{
		return;
	}
	
	// Set color and alpha
	SDL_SetTextureColorMod(mpTexture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(mpTexture, color.a);

	// Set blend mode
	SDL_SetTextureBlendMode(mpTexture, SDL_BLENDMODE_BLEND);
	
	SDL_RenderCopyEx(renderer, mpTexture, clip, offset, 0.0, 0, flip);
}