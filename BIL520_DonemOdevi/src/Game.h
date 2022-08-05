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
	GameScene* get_active_scene();
private:
	unsigned int fps_goal;
	unsigned int fixed_steps;
	bool is_running;
	GLFWwindow* game_window;
	SceneManager scene_manager;
	GameRenderer* renderer;
	void fixed_update();
	void update();
	void render();
};