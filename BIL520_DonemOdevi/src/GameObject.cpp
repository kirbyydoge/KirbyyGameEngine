#include "GameObject.h"

id_t GameObject::id_ctr = 0;
std::unordered_map<id_t, GameObject*> GameObject::objects;

GameObject::GameObject(id_t id, std::string name) : GameObject(id, name, glm_ext::new_vec3(0.f, 0.f, 0.f)) {}

GameObject::GameObject(id_t id, std::string name, glm::vec3 pos) {
	this->id = id;
	this->name = name;
	transform.set_pos(pos);
	transform.set_scale(glm_ext::new_vec3(0.f, 0.f, 0.f));
	transform.set_rotation(glm_ext::new_vec3(0.f, 0.f, 0.f));
}

GameObject::~GameObject() {

}

GameObject& GameObject::instantiate_object(std::string name) {
	GameObject* obj = new GameObject(GameObject::id_ctr, name, glm_ext::new_vec3(0.f, 0.f, 0.f));
	GameObject::objects[GameObject::id_ctr++] = obj;
	return *obj;
}

GameObject& GameObject::instantiate_object(std::string name, glm::vec3 pos) {
	GameObject* obj = new GameObject(GameObject::id_ctr, name, pos);
	GameObject::objects[GameObject::id_ctr++] = obj;
	return *obj;
}

template <class T>
void GameObject::add_component(const T* component) {
	components[typeid(T)] = component;
	if (std::is_base_of<RenderableComponent, T>) {
		renderable_components.push_back(component);
	}
	if (std::is_base_of<LiveComponent, T>) {
		live_components.push_back(component);
	}
}

template <class T>
T* GameObject::get_component() {
	auto& component = components.find(typeid(T));
	if (component != components.end()) {
		return component.second;
	}
	return NULL;
}

void GameObject::start() {
	for (auto comp : components) {
		comp.second->start();
	}
}

void GameObject::fixed_update() {
	for (auto comp : live_components) {
		comp->fixed_update();
	}
}

void GameObject::early_update() {
	for (auto comp : live_components) {
		comp->early_update();
	}
}

void GameObject::update() {
	for (auto comp : live_components) {
		comp->update();
	}
}

void GameObject::late_update() {
	for (auto comp : live_components) {
		comp->late_update();
	}
}

void GameObject::stop() {
	for (auto& comp : components) {
		comp.second->stop();
	}
}

id_t GameObject::get_id() {
	return id;
}

std::string GameObject::get_name() {
	return name;
}

std::unordered_map<id_t, ObjectComponent*>& GameObject::get_components() {
	return components;
}

std::vector<RenderableComponent*>& GameObject::get_renderable_components() {
	return renderable_components;
}