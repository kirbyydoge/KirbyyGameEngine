#pragma once
#include "Game.h"

class Application {
public:
	static void set_game(Game* game);
	static Game* game;
};