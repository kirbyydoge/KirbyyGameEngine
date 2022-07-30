#include "Game.h"
#include "GameTime.h"
#include "GameWindow.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
	Shader shader("res/shaders/vshader.glsl", "res/shaders/fshader.glsl");
	float delta_time = 0;
	float positions[] = {
		-1.5f, -1.5f, 0.0f, 0.0f,
		 1.5f, -1.5f, 1.0f, 0.0f,
		 1.5f,  1.5f, 1.0f, 1.0f,
		-1.5f,  1.5f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	IndexBuffer ib(indices, 6);
	VertexBufferAttributes vba;
	Texture texture("res/textures/amogus.png");
	Texture texture_temp("res/textures/3dsaulgoodman.png");
	vba.push<float>(2);
	vba.push<float>(2);
	va.add_buffer(vb, vba);
	std::pair<int, int> window_sizes = GameWindow::get_size(game_window);
	float aspect_ratio = (float)window_sizes.first / window_sizes.second;
	float proj_height = 1.5f;
	float proj_width = proj_height * aspect_ratio;
	glm::mat4 proj = glm::ortho(-proj_width, proj_width, -proj_height, proj_height, -1.0f, 1.0f);
	float red = 0.0f;
	float inc = 0.05f;
	while (!glfwWindowShouldClose(game_window) && is_running) {
		// update(); <temp section>
		if (red > 1.0f) {
			inc = -0.05f;
		}
		else if (red < 0.0f) {
			inc = 0.05f;
		}
		red += inc;
		// render(); <temp section>
		renderer->clear();
		texture_temp.bind(1);
		shader.set_uniform<int>("u_texture", 1);
		shader.set_uniform_matrix<glm::mat4>("u_model_proj", proj);
		renderer->draw(va, ib, shader);
		texture.bind(0);
		shader.set_uniform<int>("u_texture", 0);
		shader.set_uniform_matrix<glm::mat4>("u_model_proj", proj);
		renderer->draw(va, ib, shader);
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
	renderer->render_scene(*scene_manager.get_active_scene());
}