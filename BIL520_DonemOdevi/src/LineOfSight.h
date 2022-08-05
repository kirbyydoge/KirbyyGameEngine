#pragma once
#include "LiveComponent.h"
#include "GameObject.h"
#include "GameInput.h"
#include "GLFW/glfw3.h"
#include "glm/gtx/rotate_vector.hpp"
#include "Line.h"
#include "Mesh2D.h"

#include <vector>
#include <set>
#include <algorithm>

class LineOfSight : public LiveComponent {
public:
	LineOfSight(glm::vec2 screen_size, glm::vec2 camera_pos, glm::vec2 camera_size) {
		this->screen_size = screen_size;
		this->camera_pos = camera_pos;
		this->camera_size = camera_size;
		base = nullptr;
		center = nullptr;
		scene = nullptr;
		mesh = nullptr;
		fov = 70;
		num_casts = 17;
	}
	virtual void start() override {
		std::cout << "Screen: " << screen_size.x << " " << screen_size.y << std::endl;
		std::cout << "Screen: " << camera_pos.x << " " << camera_pos.y << std::endl;
		std::cout << "Screen: " << camera_size.x << " " << camera_size.y << std::endl;
		base = this->get_base();
		center = &this->get_base()->get_transform();
		scene = this->get_base()->get_scene();
		mesh = new Mesh2D;
		mesh->set_draw_order(100);
		use_lines = false;
	}
	virtual void late_update() override {
		build_line_of_sight();
	}
private:
	bool use_lines;
	float fov;
	int num_casts;
	glm::vec2 screen_size;
	glm::vec2 camera_pos;
	glm::vec2 camera_size;
	GameObject* base;
	GameScene* scene;

	Transform* center;
	std::vector<Line> lines;
	Mesh2D* mesh;

	void build_line_of_sight() {
		lines.clear();
		std::pair<float, float> mpos = GameInput::get_mouse_pos();
		glm::vec2 world_pos = screen_to_world(mpos.first, mpos.second);
		glm::vec3 origin = center->get_pos();
		glm::vec3 dir = glm::normalize(glm::vec3(world_pos.x, world_pos.y, 0.0f) - origin);
		glm::vec3 normal = glm::vec3(0.0f, 0.0f, 1.0f);
		float distance = 10.0f;
		std::set<GameObject*> hit_list;
		std::vector<std::pair<float, glm::vec3>> ray_vertices;
		GameObject* last_hit = nullptr;
		auto renderables = scene->get_renderable_objects();
		for (auto obj : renderables) {
			if (obj->get_tag() == GameObjectTag::TARGET) {
				Sprite* sprite = obj->get_component<Sprite>();
				if (sprite) {
					sprite->disable();
				}
			}
		}
		for (int i = 0; i < num_casts; i++) {
			float cur_angle = glm::radians(i * fov / (num_casts - 1) - fov / 2);
			glm::vec3 cast_dir = glm::rotateZ(dir, cur_angle);
			glm::vec3 end = origin + cast_dir * distance;
			RayInfo cast_info;
			cast_info.hit = nullptr;
			cast_info.origin = center->get_pos();
			cast_info.direction = cast_dir;
			cast_info.t = distance;
			GameObject* obj_hit = nullptr;
			auto cast_result = scene->raycast(center->get_pos(), cast_dir, distance);
			for (auto info : cast_result) {
				if (info.hit->get_base()->get_tag() != GameObjectTag::OBSTACLE) {
					continue;
				}
				if (info.hit && info.t < cast_info.t) {
					cast_info = info;
				}
			}
			for (auto info : cast_result) {
				if (info.hit->get_base()->get_tag() != GameObjectTag::TARGET) {
					continue;
				}
				if (info.t < cast_info.t) {
					Sprite* sprite = info.hit->get_base()->get_component<Sprite>();
					if (sprite) {
						sprite->enable();
					}
				}
			}
			if (cast_info.hit) {
				obj_hit = cast_info.hit->get_base();
				end = cast_info.origin + cast_info.direction * cast_info.t;
			}
			if (obj_hit != last_hit) {
				if (i > 0) {
					GameObject* target = obj_hit ? obj_hit : last_hit;
					float prev_angle = glm::radians((i - 1) * fov / (num_casts - 1) - fov / 2);
					find_corner(base, target, origin, dir, prev_angle, cur_angle, distance, obj_hit != nullptr, ray_vertices, 6);
				}
				last_hit = obj_hit;
			}
			ray_vertices.push_back(std::make_pair(cur_angle, end));
		}
		std::sort(ray_vertices.begin(), ray_vertices.end(), [](auto& left, auto& right) { return left.first < right.first; });
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		vertices.push_back(origin.x);
		vertices.push_back(origin.y);
		int cur_idx = 0;
		for (auto v : ray_vertices) {
			vertices.push_back(v.second.x);
			vertices.push_back(v.second.y);
			cur_idx++;
			if (cur_idx > 1) {
				indices.push_back(0);
				indices.push_back(cur_idx - 1);
				indices.push_back(cur_idx);
			}
		}
		mesh->set_data(&vertices[0], sizeof(float) * vertices.size());
		mesh->set_index(&indices[0], indices.size());
		scene->add_render_once(mesh);
		auto& anims = scene->get_renderable_objects();
		for (auto obj : anims) {
			if (hit_list.find(obj) == hit_list.end()) {
				SaulGoodman* anim = obj->get_component<SaulGoodman>();
				if (anim) {
					anim->set_sprite(0);
				}
			}
		}
	}

	glm::vec3 find_corner(GameObject* base, GameObject* target, glm::vec3 origin, glm::vec3 direction,
		float start_angle, float end_angle, float distance, bool hit_on_end,
		std::vector<std::pair<float, glm::vec3>>& ray_vertices, int depth) {
		if ((end_angle - start_angle) < 0.0017f || depth == 0) {
			float angle = hit_on_end ? end_angle : start_angle;
			glm::vec3 dir = glm::rotateZ(direction, angle);
			RayInfo res = raycast_closest_obstacle(origin, dir, distance);
			glm::vec3 vertex = res.origin + res.direction * res.t;
			return vertex;
		}
		float pivot = (end_angle + start_angle) / 2;
		glm::vec3 pivot_dir = glm::rotateZ(direction, pivot);
		RayInfo res = raycast_closest_obstacle(origin, pivot_dir, distance);
		bool hit_on_pivot = res.hit && res.hit->get_base() == target;
		glm::vec3 vertex = res.origin + res.direction * (res.hit ? res.t : distance);
		ray_vertices.push_back(std::make_pair(pivot, vertex));
		if (hit_on_pivot == hit_on_end) {
			return find_corner(base, target, origin, direction, start_angle, pivot, distance, hit_on_pivot, ray_vertices, depth - 1);
		}
		else {
			return find_corner(base, target, origin, direction, pivot, end_angle, distance, hit_on_end, ray_vertices, depth - 1);
		}
	}

	RayInfo raycast_closest_obstacle(glm::vec3 origin, glm::vec3 cast_dir, float distance) {
		RayInfo cast_info;
		cast_info.hit = nullptr;
		cast_info.origin = origin;
		cast_info.direction = cast_dir;
		cast_info.t = distance;
		auto cast_result = scene->raycast(origin, cast_dir, distance);
		for (auto info : cast_result) {
			if (info.hit->get_base() == base) {
				continue;
			}
			if (info.hit && info.t < cast_info.t &&
					info.hit->get_base()->get_tag() == GameObjectTag::OBSTACLE) {
				cast_info = info;
			}
		}
		return cast_info;
	}

	glm::vec2 screen_to_world(int x, int y) {
		glm::vec2 world_pos(
			(float)x * camera_size.x / screen_size.x - camera_size.x / 2,
			(float)camera_size.y / 2 - y * camera_size.y / screen_size.y
		);
		return world_pos;
	}

};