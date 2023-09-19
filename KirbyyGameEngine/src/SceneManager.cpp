#include "SceneManager.h"

SceneManager::SceneManager() {
	this->active_scene = nullptr;
}

SceneManager::~SceneManager() {
	destroy_scene();
}

void SceneManager::load_scene(GameScene* scene) {
	active_scene = scene;
	active_scene->load();
}

void SceneManager::destroy_scene() {
	active_scene->destroy();
}

GameScene* SceneManager::get_active_scene() {
	return active_scene;
}