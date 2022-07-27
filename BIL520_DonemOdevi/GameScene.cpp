#include "GameScene.h"

GameScene::GameScene(std::string name) {
	this->name = name;
}
GameScene::~GameScene() {}

void GameScene::add_object(GameObject* obj) {
	scene_objects[obj->get_id()] = obj;
}

GameObject* GameScene::get_object(id_t id) {
	auto search = scene_objects.find(id);
	if (search != scene_objects.end()) {
		return search->second;
	}
	return nullptr;
}

void GameScene::load() {
	for (auto& obj : scene_objects) {
		obj.second->start();
	}
}

void GameScene::fixed_update() {
	for (auto& obj : scene_objects) {
		obj.second->fixed_update();
	}
}

void GameScene::update() {
	for (auto& obj : scene_objects) {
		obj.second->early_update();
	}
	for (auto& obj : scene_objects) {
		obj.second->update();
	}
	for (auto& obj : scene_objects) {
		obj.second->late_update();
	}
}

void GameScene::destroy() {
	for (auto& obj : scene_objects) {
		obj.second->stop();
	}
}