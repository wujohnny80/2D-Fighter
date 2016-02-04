//====================================================================================================
// Filename:	ImageLoader.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "ImageLoader.h"

#include <stdio.h>
#include <assert.h>

#include "GraphicSystem.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

SDL_Texture* ImageLoader::Load(const char* filePath)
{
	// Final texture
	SDL_Texture* newTexture = nullptr;

	// Load image
	SDL_Surface* loadedSurface = IMG_Load(filePath);

	// Verify it was loaded
	if (loadedSurface == nullptr)
	{
		printf("Image at %s could not be loaded! SDL_image Error: %s\n", filePath, IMG_GetError());
	}
	else
    {
		// Get renderer and the window from graphics system
		SDL_Renderer* renderer = GraphicSystem::Instance().GetRenderer();

        // Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if( newTexture == nullptr )
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", filePath, SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

	return newTexture;
}