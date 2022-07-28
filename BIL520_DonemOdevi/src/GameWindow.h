#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>
#include <utility>

class GameWindow {
public:
	static GLFWwindow* create_window(int width, int height, std::string window_name);
	std::pair<int, int> get_size(GLFWwindow* window);
	static int get_width(GLFWwindow* window);
	static int get_height(GLFWwindow* window);
};