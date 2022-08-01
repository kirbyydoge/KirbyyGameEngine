#include "GameScene.h"
#include <type_traits>
#include <iostream>

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

void GameScene::add_renderable(GameObject* obj) {
	auto obj_comps = obj->get_renderable_components();
	for (auto comp : obj_comps) {
		renderable_components.push_back(comp);
	}
	renderable_objects.push_back(obj);
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