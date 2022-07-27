#include "Game.h"
#include "GameTime.h"
#include "GameWindow.h"
#include <iostream>

Game::Game(int width, int height, std::string window_name) {
	game_window = nullptr;
	is_running = false;
	if (!glfwInit()) {
		std::cout << "Could not initialize GLFW." << std::endl;
		return;
	}
	game_window = GameWindow::create_window(width, height, window_name);
	if (!game_window) {
		glfwTerminate();
		std::cout << "Could not create game window." << std::endl;
		return;
	}
	renderer = GameRenderer::get_renderer();
}

Game::~Game() {
	glfwDestroyWindow(game_window);
	glfwTerminate();
}

void Game::run() {
	is_running = true;
	float delta_time = 0;
	while (is_running) {
		update();
		render();
	}
}

GLFWwindow* Game::get_game_window() {
	return game_window;
}

void Game::update() {
	
}

void Game::render() {
	
}