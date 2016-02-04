//====================================================================================================
// Filename:	GraphicSystem.h
// Created by:	Johnny Wu
// Description:	Singleton Class for the graphics system.
//====================================================================================================
#ifndef _GRAPHICSYSTEM_H_
#define _GRAPHICSYSTEM_H_

#include <SDL.h>
#include <SDL_image.h>

//====================================================================================================
// Class Declarations
//====================================================================================================

class GraphicSystem
{
public:
	static GraphicSystem& Instance()	{ static GraphicSystem instance; return instance; }
	~GraphicSystem();

	// Functions to startup and shutdown the graphics system
	void Initialize(SDL_Window* window);
	void Terminate();

	// Functions to be called before and after any rendering
	void BeginRender();
	void EndRender();

	SDL_Renderer* GetRenderer()	const	{ return mpRenderer; }
	SDL_Window* GetWindow()	const		{ return mpWindow; }

private:
	GraphicSystem();
	GraphicSystem(GraphicSystem const&);	// Don't implement
	void operator=(GraphicSystem const&);	// Don't implement

	SDL_Renderer* mpRenderer;
	SDL_Window* mpWindow;

	bool mInitialized;						// Init flag
};

#endif // #ifndef _GRAPHICSYSTEM_H_