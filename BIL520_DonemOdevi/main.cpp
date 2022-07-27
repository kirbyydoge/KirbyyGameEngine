#include <GLFW/glfw3.h>
#include "Application.h"
#include "Game.h"

int main(void) {
	Game *game = new Game(640, 480, "Fine, I'll do it myself.");
	Application::set_game(game);
	return 0;
}