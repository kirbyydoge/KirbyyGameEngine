#include "Game.h"
#include "GameTime.h"
#include "GameWindow.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GameScene.h"
#include "BaseScene.h"

#include <chrono>
#include <thread>
#include <iostream>

#define ELAPSED_MILLIS(begin, end) (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count())
#define ELAPSED_MICROS(begin, end) (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())

#define ASSERT(x) if (!(x)) __debugbreak();
#define GL_CALL(x) gl_clear_errors();\
	x;\
	ASSERT(gl_log_error(#x, __FILE__, __LINE__))

static void gl_clear_errors() {
	while (glGetError() != GL_NO_ERROR);
}

static bool gl_log_error(const char* function, const char* file, int line) {
	while (unsigned int error = glGetError()) {
		std::cout << "GL ERR: " << error << std::endl;
		std::cout << function << " at " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

Game::Game(int width, int height, std::string window_name) {
	game_window = nullptr;
	renderer = nullptr;
	is_running = false;
	fps_goal = 60;
	fixed_steps = 60;
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
	GameTime::set_fixed_delta_time((float)1 / fixed_steps);
}

Game::~Game() {
	glfwDestroyWindow(game_window);
	glfwTerminate();
}

void Game::run() {
	is_running = true;
	BaseScene* base = new BaseScene("TestScene");
	base->setup();
	scene_manager.load_scene(base);
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	begin = std::chrono::steady_clock::now();
	end = std::chrono::steady_clock::now();
	unsigned long long int frame_time = 0;
	unsigned long long int frame_goal = (float)1000000 / fps_goal;
	unsigned long long int fixed_time = (float)1000000 / fixed_steps;
	unsigned long long int fixed_bank = 0;
	while (!glfwWindowShouldClose(game_window) && is_running) {
		unsigned long long int us_delta_time = ELAPSED_MICROS(begin, end);
		GameTime::set_delta_time((float)us_delta_time / 1000000);
		fixed_bank += us_delta_time;
		begin = std::chrono::steady_clock::now();
		while (fixed_bank > fixed_time) {
			fixed_update();
			fixed_bank -= fixed_time;
		}
		update();
		render();
		frame_time = ELAPSED_MICROS(begin, std::chrono::steady_clock::now());
		if (frame_time < frame_goal) {
			std::this_thread::sleep_until(begin + std::chrono::microseconds(frame_goal));
		}
		end = std::chrono::steady_clock::now();
	}
}

GLFWwindow* Game::get_game_window() {
	return game_window;
}

void Game::fixed_update() {
	scene_manager.get_active_scene()->fixed_update();
}

void Game::update() {
	scene_manager.get_active_scene()->update();
}

void Game::render() {
	renderer->render_scene(scene_manager.get_active_scene(), game_window);
}