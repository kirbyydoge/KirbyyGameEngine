#pragma once
#include "GameScene.h"

class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void load_scene(GameScene* scene);
	void destroy_scene();
	GameScene* get_active_scene();
private:
	GameScene* active_scene;
};