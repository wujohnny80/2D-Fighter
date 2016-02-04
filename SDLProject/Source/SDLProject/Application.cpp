//====================================================================================================
// Filename:	Application.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "Application.h"

#include <stdio.h>
#include <assert.h>

#include "CollisionSystem.h"
#include "GraphicSystem.h"
#include "InputManager.h"

int Application::screenHeight;
int Application::screenWidth;

Application::Application()
	: mpWindow(nullptr)
{
}

//----------------------------------------------------------------------------------------------------

Application::~Application()
{
}

//----------------------------------------------------------------------------------------------------

void Application::Initialize(const char* appName, int width, int height)
{
	// Cache window dimesion
	screenWidth = width;
	screenHeight = height;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}

	// Create window
	mpWindow = SDL_CreateWindow(appName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if(mpWindow == nullptr)
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	// Create and initialize all engine systems
	GraphicSystem::Instance().Initialize(mpWindow);
	InputManager::Instance().Initialize();
	CollisionSystem::Instance().Initialize(screenWidth, screenHeight);

	// User init logic
	InitGame();
}

//----------------------------------------------------------------------------------------------------

void Application::Update()
{
	SDL_Event evnt;
	bool isRunning = true;
	while (isRunning)
	{
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type) 
			{
			case SDL_QUIT:
				SDL_Quit();
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				InputManager::Instance().PressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				InputManager::Instance().ReleaseKey(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				InputManager::Instance().SetMouse(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				InputManager::Instance().PressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				InputManager::Instance().ReleaseKey(evnt.button.button);
				break;
			}
		}
		
		// Update Collision System
		CollisionSystem::Instance().Update();

		// Update Timer
	
		// Update Input
		InputManager::Instance().Update();

		// Begin scene
		GraphicSystem::Instance().BeginRender();

		// User update logic
		RunGame();

		// End scene
		GraphicSystem::Instance().EndRender();
	}
}

//----------------------------------------------------------------------------------------------------

void Application::Terminate()
{
	// User clean up logic
	StopGame();

	// Shutdown all engine systems
	CollisionSystem::Instance().Terminate();
	InputManager::Instance().Terminate();
	GraphicSystem::Instance().Terminate();

	// Destroy the window
	SDL_DestroyWindow(mpWindow);
	mpWindow = nullptr;
}