#include "GameInput.h"
#include "GameWindow.h"
#include "Application.h"
#include "GLFW/glfw3.h"

bool GameInput::is_pressed(int key_code) {
	auto* window = Application::game->get_game_window();
	int state = glfwGetKey(window, key_code);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool GameInput::is_mouse_pressed(int button) {
	auto* window = Application::game->get_game_window();
	int state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

std::pair<float, float> GameInput::get_mouse_pos() {
	auto* window = Application::game->get_game_window();
	double mouse_x;
	double mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	return std::make_pair<float, float>((float)mouse_x, (float)mouse_y);
}

float GameInput::get_mouse_x() {
	auto* window = Application::game->get_game_window();
	double mouse_x;
	double mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	return (float)mouse_x;
}

float GameInput::get_mouse_y() {
	auto* window = Application::game->get_game_window();
	double mouse_x;
	double mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
	return (float)mouse_y;
}