#include "Game.h"
#include "GameTime.h"
#include "GameWindow.h"
#include <iostream>

Game::Game(int width, int height, std::string window_name) {
	game_window = nullptr;
	renderer = nullptr;
	is_running = false;
	if (!glfwInit()) {
		std::cout << "Could not initialize GLFW." << std::endl;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
	scene_manager.get_active_scene()->update();
}

void Game::render() {
	renderer->render(*scene_manager.get_active_scene());
}