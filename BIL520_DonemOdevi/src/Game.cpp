#include "Game.h"
#include "GameTime.h"
#include "GameWindow.h"

#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include <chrono>
#include <thread>
#include <iostream>

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
	Shader program("res/shaders/vshader.glsl", "res/shaders/fshader.glsl");
	unsigned int loc_color = glGetUniformLocation(program.id, "u_color");
	float delta_time = 0;
	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));
	IndexBuffer ib(indices, 6);
	VertexBufferAttributes vba;
	vba.push<float>(2);
	va.add_buffer(vb, vba);
	float red = 0.0f;
	float inc = 0.05f;
	while (is_running) {
		// update();
		// render();
		glClear(GL_COLOR_BUFFER_BIT);
		program.use();
		glUniform4f(loc_color, red, 0.3f, 0.8f, 1.0f);
		va.bind();
		ib.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		if (red > 1.0f) {
			inc = -0.05f;
		}
		else if (red < 0.0f) {
			inc = 0.05f;
		}
		red += inc;
		glfwSwapBuffers(game_window);
		glfwPollEvents();
		//std::this_thread::sleep_for(std::chrono::milliseconds(15));
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