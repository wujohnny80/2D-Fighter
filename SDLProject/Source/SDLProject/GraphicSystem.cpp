//====================================================================================================
// Filename:	GraphicSystem.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "GraphicSystem.h"
#include <stdio.h>

//====================================================================================================
// Class Definitions
//====================================================================================================

GraphicSystem::GraphicSystem()
	: mpRenderer(nullptr)
	, mpWindow(nullptr)
	, mInitialized(false)
{
}

//----------------------------------------------------------------------------------------------------

GraphicSystem::~GraphicSystem()
{
}

//----------------------------------------------------------------------------------------------------

void GraphicSystem::Initialize(SDL_Window* window)
{
	// Cache the window
	mpWindow = window;

	// Do Initialization
	mpRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if( mpRenderer == nullptr )
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		mInitialized = false;
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(mpRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		// Initialize PNG and JPG support
		if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
		{
			printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			mInitialized = false;
		}
		// Set flag
		mInitialized = true;
	}
}

//----------------------------------------------------------------------------------------------------

void GraphicSystem::Terminate()
{
	//Destroy window
	SDL_DestroyRenderer(mpRenderer);
	mpRenderer = nullptr;

	// Set flag
	mInitialized = false;
}

//----------------------------------------------------------------------------------------------------

void GraphicSystem::BeginRender()
{
	// Clear screen to black
	SDL_SetRenderDrawColor(mpRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mpRenderer);
}

void GraphicSystem::EndRender()
{
	//Update screen
	SDL_RenderPresent(mpRenderer);
}