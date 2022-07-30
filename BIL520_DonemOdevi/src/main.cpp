#include "Application.h"
#include "Game.h"
#include <iostream>

int main(void) {
	Game *game = new Game(1024, 768, "Fine, I'll do it myself.");
	Application::set_game(game);
	game->run();
	return 0;
}