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

void GameScene::fixed_update() {
	for (auto& obj : live_objects) {
		obj->fixed_update();
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