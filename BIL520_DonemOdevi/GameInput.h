#pragma once
#include <utility>

class GameInput {
public:
	inline static bool is_pressed(int key_code);
	inline static bool is_mouse_pressed(int button);
	inline static std::pair<float, float> get_mouse_pos();
	inline static float get_mouse_x();
	inline static float get_mouse_y();
};