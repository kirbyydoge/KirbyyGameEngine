#pragma once
#include "ObjectComponent.h"
#include "Transform.h"
#include "glm_extended.h"

#include <utility>

#include <string>
#include <unordered_map>

typedef uint64_t id_t;

class GameObject {
public:
	static GameObject& instantiate_object(std::string name);
	static GameObject& instantiate_object(std::string name, glm::vec3 pos);
	~GameObject();
	void start();
	void fixed_update();
	void early_update();
	void update();
	void late_update();
	void stop();
	id_t get_id();
	std::string get_name();
	template <class T> void add_component(const T* component);
	template <class T> T* get_component();
private:
	static id_t id_ctr;
	static std::unordered_map<id_t, GameObject*> objects;
	GameObject(id_t id, std::string name);
	GameObject(id_t id, std::string name, glm::vec3 pos);
	id_t id;
	std::string name;
	Transform transform;
	std::unordered_map<id_t, ObjectComponent*> components;
};