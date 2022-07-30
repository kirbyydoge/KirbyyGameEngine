#pragma once
#include "LiveComponent.h"
#include "GameTime.h"
#include "GameInput.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "GameObject.h"

class PlayerMovement : public LiveComponent {
public:
	virtual void update() override {
		glm::vec3 pos = get_base()->get_transform().get_pos();
		if (GameInput::is_pressed(GLFW_KEY_W)) {
			pos[1] += speed * GameTime::delta_time;
		}
		if (GameInput::is_pressed(GLFW_KEY_S)) {
			pos[1] -= speed * GameTime::delta_time;
		}
		if (GameInput::is_pressed(GLFW_KEY_A)) {
			pos[0] -= speed * GameTime::delta_time;
		}
		if (GameInput::is_pressed(GLFW_KEY_D)) {
			pos[0] += speed * GameTime::delta_time;
		}
		get_base()->get_transform().set_pos(pos);
	};
private:
	float speed = 5.0f;
};