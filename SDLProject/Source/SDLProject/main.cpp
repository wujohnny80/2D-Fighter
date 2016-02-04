#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <time.h>
#include <typeinfo>

#include "GameManager.h"

const char* APP_NAME = "My Game";
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 800;

int main(int argc, char* args[])
{
	// Seed rand
	srand ( time(NULL) );

	// Initialize and run the game
	GameManager game;
	game.Initialize(APP_NAME, WIN_WIDTH, WIN_HEIGHT);
	game.Update();
	game.Terminate();
	return 0;
}