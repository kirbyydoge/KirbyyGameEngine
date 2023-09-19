#pragma once
#include "LiveComponent.h"
#include "GameTime.h"
#include "GameInput.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "GameObject.h"
#include "Box2D.h"
#include <math.h>

class PlayerMovement : public LiveComponent {
public:
	virtual void start() override {
		transform = &get_base()->get_transform();
		collider = get_base()->get_component<Collider2D>();
		velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	virtual void fixed_update() override {
		glm::vec3 pos = transform->get_pos();
		transform->set_pos(pos + velocity * GameTime::fixed_delta_time);
	}
	virtual void update() override {
		velocity.x = 0;
		velocity.y = 0;
		if (GameInput::is_pressed(GLFW_KEY_W)) {
			velocity.y = speed;
		}
		if (GameInput::is_pressed(GLFW_KEY_S)) {
			velocity.y = -speed;
		}
		if (GameInput::is_pressed(GLFW_KEY_A)) {
			velocity.x = -speed;
		}
		if (GameInput::is_pressed(GLFW_KEY_D)) {
			velocity.x = speed;
		}
	};
	virtual void on_collision(Collider2D* other) override {
		glm::vec3 other_pos = other->get_base()->get_transform().get_pos();
		glm::vec3 cur_pos = transform->get_pos();
		glm::vec3 other_dir = other_pos - cur_pos;
		glm::vec2 cur_dims = dynamic_cast<Box2D*>(collider->get_bounds())->get_dimensions();
		glm::vec2 other_dims = dynamic_cast<Box2D*>(other->get_bounds())->get_dimensions();
		float horz_dist = abs(other_pos.x - cur_pos.x);
		float horz_width = (cur_dims.x + other_dims.x) / 2;
		float vert_dist = abs(other_pos.y - cur_pos.y);
		float vert_width = (cur_dims.y + other_dims.y) / 2;
		if (sgn(other_dir.x) == sgn(velocity.x)) {
			velocity.x = 0;
		}
		if (sgn(other_dir.y) == sgn(velocity.y)) {
			velocity.y = 0;
		}
		if (horz_dist < horz_width && vert_dist <= horz_dist) {
			float offset = horz_width - horz_dist;
			cur_pos.x -= sgn(other_dir.x) * offset;
		}
		if (vert_dist < vert_width && horz_dist <= vert_dist) {
			float offset = vert_width - vert_dist;
			cur_pos.y -= sgn(other_dir.y) * offset;
		}
		transform->set_pos(cur_pos);
	}
private:
	float speed = 5.0f;
	glm::vec3 velocity;
	Transform* transform;
	Collider2D* collider;

	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}
};