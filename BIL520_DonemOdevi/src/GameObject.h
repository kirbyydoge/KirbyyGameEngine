#pragma once
#include "ObjectComponent.h"
#include "LiveComponent.h"
#include "RenderableComponent.h"
#include "Transform.h"
#include "glm_extended.h"
#include "Collider2D.h"

#include <utility>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <unordered_map>
#include <iostream>

typedef uint64_t id_t;

class GameScene;

class GameObject {
public:
	static GameObject& instantiate_object(GameScene* scene, std::string name);
	static GameObject& instantiate_object(GameScene* scene, std::string name, glm::vec3 pos);
	~GameObject();
	void start();
	void fixed_update();
	void early_update();
	void update();
	void late_update();
	void stop();
	void on_collision(Collider2D* other);
	id_t get_id();
	std::string get_name();
	GameScene* get_scene();
	Transform& get_transform();
	std::unordered_map<std::type_index, ObjectComponent*>& get_components();
	std::vector<RenderableComponent*>& get_renderable_components();
	template <class T> void add_component(T* component) {
		components[std::type_index(typeid(T))] = component;
		component->set_base(this);
		if (std::is_base_of<RenderableComponent, T>::value) {
			renderable_components.push_back((RenderableComponent*) component);
		}
		if (std::is_base_of<LiveComponent, T>::value) {
			live_components.push_back((LiveComponent*) component);
		}
	}
	template <class T> T* get_component() {
		auto component = components.find(std::type_index(typeid(T)));
		if (component != components.end()) {
			return (T*) component->second;
		}
		return nullptr;
	}
private:
	static id_t id_ctr;
	static std::unordered_map<id_t, GameObject*> objects;
	GameScene* scene;
	GameObject(id_t id, std::string name);
	GameObject(id_t id, std::string name, glm::vec3 pos);
	id_t id;
	std::string name;
	Transform transform;
	std::unordered_map<std::type_index, ObjectComponent*> components;
	std::vector<LiveComponent*> live_components;
	std::vector<RenderableComponent*> renderable_components;
};