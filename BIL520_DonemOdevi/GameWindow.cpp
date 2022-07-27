#include "GameWindow.h"

GLFWwindow* GameWindow::create_window(int width, int height, std::string window_name) {
	GLFWwindow* window;
	if (!glfwInit()) {
		std::cout << "ERR: Could not initialize GLFW." << std::endl;
		return nullptr;
	}
	window = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);
	if (!window) {
		std::cout << "ERR: Could not initialize game window." << std::endl;
		return nullptr;
	}
	return window;
}

std::pair<int, int> GameWindow::get_size(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return std::make_pair(width, height);
}

int GameWindow::get_width(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

int GameWindow::get_height(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return height;
}
