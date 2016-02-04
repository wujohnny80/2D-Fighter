//====================================================================================================
// Filename:	Application.h
// Created by:	Johnny Wu
// Description:	Class for creating a window application.
//====================================================================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SDL.h>

class Application
{
public:
	Application();
	virtual ~Application();

	// Top layer of the application, starting point called in main.
	void Initialize(const char* appName, int width, int height);
	void Update();
	void Terminate();

	static int screenWidth;
	static int screenHeight;

protected:
	// Functions to be implemented by user in the Game Manager class.
	virtual void InitGame() = 0;
	virtual void RunGame() = 0;
	virtual void StopGame() = 0;

	// Members
	SDL_Window* mpWindow;
};

#endif // #ifndef _APPLICATION_H_