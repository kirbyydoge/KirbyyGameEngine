#pragma once
#include <string>
#include <unordered_map>

#include "GameObject.h"

class GameScene {
public:
	GameScene(std::string name);
	~GameScene();
	void add_object(GameObject* obj);
	GameObject* get_object(id_t id);
	void load();
	void fixed_update();
	void update();
	void destroy();
private:
	std::string name;
	std::unordered_map<id_t, GameObject*> scene_objects;
};