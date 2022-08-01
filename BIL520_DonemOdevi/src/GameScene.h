#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "GameObject.h"
#include "LiveComponent.h"
#include "RenderableComponent.h"
#include "Collider2D.h"

class GameScene {
public:
	GameScene(std::string name);
	~GameScene();
	void add_object(GameObject* obj);
	GameObject* get_object(id_t id);
	void add_collider2D(Collider2D* collider);
	void add_renderable(GameObject* obj);
	void add_live_object(GameObject* obj);
	std::vector<GameObject*>& get_renderable_objects();
	std::vector<RenderableComponent*>& get_renderable_components();
	virtual void setup() {}
	void load();
	void check_collisions();
	void fixed_update();
	void update();
	void destroy();
private:
	std::string name;
	std::unordered_map<id_t, GameObject*> scene_objects;
	std::vector<GameObject*> renderable_objects;
	std::vector<RenderableComponent*> renderable_components;
	std::vector<Collider2D*> collision2D_components;
	std::vector<GameObject*> live_objects;
	std::vector<std::pair<GameObject*, Collider2D*>> colliding_objects;
};