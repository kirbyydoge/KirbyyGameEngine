#pragma once
#include "LiveComponent.h"
#include "GameObject.h"
#include "GameInput.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/rotate_vector.hpp"
#include "Line.h"

#include <set>

class LineOfSight : public LiveComponent {
public:
	LineOfSight(glm::vec2 screen_size, glm::vec2 camera_pos, glm::vec2 camera_size) {
		this->screen_size = screen_size;
		this->camera_pos = camera_pos;
		this->camera_size = camera_size;
		base = nullptr;
		center = nullptr;
		scene = nullptr;
		line = nullptr;
		fov = 70;
		num_casts = 13;
	}
	virtual void start() override {
		std::cout << "Screen: " << screen_size.x << " " << screen_size.y << std::endl;
		std::cout << "Screen: " << camera_pos.x << " " << camera_pos.y << std::endl;
		std::cout << "Screen: " << camera_size.x << " " << camera_size.y << std::endl;
		base = this->get_base();
		center = &this->get_base()->get_transform();
		scene = this->get_base()->get_scene();
		line = new Line[num_casts];
	}
	virtual void late_update() override {
		std::pair<float, float> mpos = GameInput::get_mouse_pos();
		glm::vec2 world_pos = screen_to_world(mpos.first, mpos.second);
		glm::vec3 origin = center->get_pos();
		glm::vec3 dir = glm::normalize(glm::vec3(world_pos.x, world_pos.y, 0.0f) - origin);
		glm::vec3 normal = glm::vec3(0.0f, 0.0f, 1.0f);
		float distance = 20.0f;
		std::set<GameObject*> hit_list;
		for (int i = 0; i < num_casts; i++) {
			float cur_angle = glm::radians(i * fov / num_casts - fov / 2);
			glm::vec3 cast_dir = glm::rotateZ(dir, cur_angle);
			glm::vec3 end = origin + cast_dir * distance;
			auto res = scene->raycast(center->get_pos(), cast_dir, distance);
			float cur_dist = 999999;
			GameObject* obj_hit = nullptr;
			for (auto ray_info : res) {
				if (ray_info.hit->get_base() == base) {
					continue;
				}
				if (ray_info.t < cur_dist) {
					end = ray_info.origin + ray_info.direction * ray_info.t;
					cur_dist = ray_info.t;
					obj_hit = ray_info.hit->get_base();
				}
			}
			if (obj_hit) {
				SaulGoodman* anim = obj_hit->get_component<SaulGoodman>();
				hit_list.insert(obj_hit);
				if (anim) {
					anim->set_sprite(1);
				}
			}
			line[i].set_pos(origin, end);
			scene->add_render_once(&line[i]);
		}
		auto& anims = scene->get_renderable_objects();
		for (auto obj : anims) {
			if (hit_list.find(obj) == hit_list.end()) {
				obj->get_component<SaulGoodman>()->set_sprite(0);
			}
		}
	}
private:
	float fov;
	int num_casts;
	glm::vec2 screen_size;
	glm::vec2 camera_pos;
	glm::vec2 camera_size;
	GameObject* base;
	GameScene* scene;

	Transform* center;
	Line* line;

	glm::vec2 screen_to_world(int x, int y) {
		glm::vec2 world_pos(
			(float)x * camera_size.x / screen_size.x - camera_size.x / 2,
			(float)camera_size.y / 2 - y * camera_size.y / screen_size.y
		);
		return world_pos;
	}

};