#pragma once
#include <utility>

class GameInput {
public:
	static bool is_pressed(int key_code);
	static bool is_mouse_pressed(int button);
	static std::pair<float, float> get_mouse_pos();
	static float get_mouse_x();
	static float get_mouse_y();
};