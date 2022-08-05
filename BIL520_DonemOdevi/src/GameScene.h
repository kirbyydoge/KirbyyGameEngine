#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "GameObject.h"
#include "LiveComponent.h"
#include "RenderableComponent.h"
#include "Collider2D.h"

class Game;

struct RayInfo {
	Collider2D* hit;
	glm::vec3 origin;
	glm::vec3 direction;
	float t;
};

class GameScene {
public:
	GameScene(std::string name);
	~GameScene();
	void add_object(GameObject* obj);
	GameObject* get_object(id_t id);
	void add_collider2D(Collider2D* collider);
	void add_renderable_object(GameObject* obj);
	void add_renderable_component(RenderableComponent* comp);
	void delete_renderable_component(RenderableComponent* comp);
	void add_render_once(RenderableComponent* renderable);
	void add_live_object(GameObject* obj);
	std::vector<GameObject*>& get_renderable_objects();
	std::vector<RenderableComponent*>& get_renderable_components();
	std::vector<RenderableComponent*>& get_render_once();
	virtual void setup() {}
	void load();
	void check_collisions();
	void fixed_update();
	void update();
	void destroy();
	std::vector<RayInfo> raycast(glm::vec3 from, glm::vec3 to, float distance);
	RayInfo check_ray(Collider2D* obj, glm::vec3 origin, glm::vec3 dir, float distance);
private:
	std::string name;
	std::unordered_map<id_t, GameObject*> scene_objects;
	std::vector<GameObject*> renderable_objects;
	std::vector<RenderableComponent*> renderable_components;
	std::vector<RenderableComponent*> render_once;
	std::vector<Collider2D*> collision2D_components;
	std::vector<GameObject*> live_objects;
	std::vector<std::pair<GameObject*, Collider2D*>> colliding_objects;
};