#include "GameWindow.h"

void window_resize_event(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* GameWindow::create_window(int width, int height, std::string window_name) {
	GLFWwindow* window;
	if (!glfwInit()) {
		std::cout << "ERR: Could not initialize GLFW." << std::endl;
		return nullptr;
	}
	window = glfwCreateWindow(width, height, window_name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		std::cout << "ERR: Could not initalize GLEW." << std::endl;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, width, height);
	glfwSetWindowSizeCallback(window, window_resize_event);
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
