#include "GameScene.h"
#include "Box2D.h"
#include <type_traits>
#include <iostream>
#include <cmath>

GameScene::GameScene(std::string name) {
	this->name = name;
}
GameScene::~GameScene() {}

void GameScene::add_object(GameObject* obj) {
	scene_objects[obj->get_id()] = obj;
}

void GameScene::add_collider2D(Collider2D* collider) {
	collision2D_components.push_back(collider);
}

void GameScene::add_renderable_object(GameObject* obj) {
	auto obj_comps = obj->get_renderable_components();
	for (auto comp : obj_comps) {
		renderable_components.push_back(comp);
	}
	renderable_objects.push_back(obj);
}

void GameScene::add_renderable_component(RenderableComponent* comp) {
	renderable_components.push_back(comp);
}

void GameScene::delete_renderable_component(RenderableComponent* comp) {
	auto pos = std::find(renderable_components.begin(), renderable_components.end(), comp);
	if (pos != renderable_components.end()) {
		renderable_components.erase(pos);
	}
}

void GameScene::add_render_once(RenderableComponent* renderable) {
	render_once.push_back(renderable);
}

void GameScene::add_live_object(GameObject* obj) {
	live_objects.push_back(obj);
}

GameObject* GameScene::get_object(id_t id) {
	auto search = scene_objects.find(id);
	if (search != scene_objects.end()) {
		return search->second;
	}
	return nullptr;
}

std::vector<GameObject*>& GameScene::get_renderable_objects() {
	return renderable_objects;
}

std::vector<RenderableComponent*>& GameScene::get_renderable_components() {
	return renderable_components;
}

std::vector<RenderableComponent*>& GameScene::get_render_once() {
	return render_once;
}

void GameScene::load() {
	for (auto& obj : live_objects) {
		obj->start();
	}
}

void GameScene::check_collisions() {
	colliding_objects.clear();
	for (int i = 0; i < collision2D_components.size(); i++) {
		Collider2D* first = collision2D_components[i];
		for (int j = i + 1; j < collision2D_components.size(); j++) {
			Collider2D* second = collision2D_components[j];
			if (first->get_static() && second->get_static()) {
				continue;
			}
			if (first->is_colliding(second)) {
				colliding_objects.push_back(std::make_pair(first->get_base(), second));
				colliding_objects.push_back(std::make_pair(second->get_base(), first));
			}
		}
	}
}

void GameScene::fixed_update() {
	for (auto& obj : live_objects) {
		obj->fixed_update();
	}
	check_collisions();
	for (auto& pair : colliding_objects) {
		pair.first->on_collision(pair.second);
	}
}

void GameScene::update() {
	for (auto& obj : live_objects) {
		obj->early_update();
	}
	for (auto& obj : live_objects) {
		obj->update();
	}
	for (auto& obj : live_objects) {
		obj->late_update();
	}
}

void GameScene::destroy() {
	for (auto& obj : live_objects) {
		obj->stop();
	}
}

RayInfo GameScene::check_ray(Collider2D* obj, glm::vec3 origin, glm::vec3 dir, float distance) {
	RayInfo result{ nullptr, origin, dir, distance };
	glm::vec3 dir_frac(1 / dir.x, 1 / dir.y, 1 / dir.z);
	std::pair<glm::vec2, glm::vec2> bounds = dynamic_cast<Box2D*>(obj->get_bounds())->get_bounds();
	glm::vec3 llc(bounds.first.x, bounds.first.y, 0);
	glm::vec3 urc(bounds.second.x, bounds.second.y, 0);
	float t1 = (llc.x - origin.x) * dir_frac.x;
	float t2 = (urc.x - origin.x) * dir_frac.x;
	float t3 = (llc.y - origin.y) * dir_frac.y;
	float t4 = (urc.y - origin.y) * dir_frac.y;
	//float t5 = (llc.z - origin.z) * dir_frac.z;
	//float t6 = (urc.z - origin.z) * dir_frac.z;
	float tmin = std::max(std::min(t1, t2), std::min(t3, t4));
	float tmax = std::min(std::max(t1, t2), std::max(t3, t4));
	if (tmax < 0) {
		result.t = tmax;
		return result;
	}
	if (tmin > tmax || tmin > distance) {
		result.t = tmax;
		return result;
	}
	result.t = tmin;
	result.hit = obj;
	return result;
}

std::vector<RayInfo> GameScene::raycast(glm::vec3 origin, glm::vec3 dir, float distance) {
	std::vector<RayInfo> collisions;
	for (auto obj : collision2D_components) {
		RayInfo check = check_ray(obj, origin, dir, distance);
		if (check.hit) {
			collisions.push_back(check);
		}
	}
	return collisions;
}
 
RayInfo GameScene::raycast_closest(GameObject* ignore, glm::vec3 origin, glm::vec3 dir, float distance) {
	RayInfo closest;
	closest.hit = nullptr;
	closest.direction = dir;
	closest.origin = origin;
	for (auto obj : collision2D_components) {
		if (obj->get_base() == ignore) {
			continue;
		}
		RayInfo check = check_ray(obj, origin, dir, distance);
		if (check.hit) {
			if (!closest.hit || check.t < closest.t) {
				closest = check;
			}
		}
	}
	return closest;
}
