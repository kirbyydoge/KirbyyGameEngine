#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "SceneManager.h"
#include "GameRenderer.h"

class Game {
public:
	Game(int width, int height, std::string window_name);
	~Game();
	void run();
	GLFWwindow* get_game_window();
private:
	bool is_running;
	GLFWwindow* game_window;
	SceneManager scene_manager;
	GameRenderer* renderer;

	void update();
	void render();
};