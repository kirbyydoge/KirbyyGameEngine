#include "Application.h"

Game* Application::game = nullptr;

void Application::set_game(Game* game) {
	Application::game = game;
}