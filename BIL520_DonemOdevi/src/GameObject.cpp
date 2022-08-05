#include "GameObject.h"
#include "GameScene.h"

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

GameObject& GameObject::instantiate_object(GameScene* scene, std::string name) {
	GameObject* obj = new GameObject(GameObject::id_ctr, name, glm_ext::new_vec3(0.f, 0.f, 0.f));
	obj->scene = scene;
	GameObject::objects[GameObject::id_ctr++] = obj;
	return *obj;
}

GameObject& GameObject::instantiate_object(GameScene* scene, std::string name, glm::vec3 pos) {
	GameObject* obj = new GameObject(GameObject::id_ctr, name, pos);
	obj->scene = scene;
	GameObject::objects[GameObject::id_ctr++] = obj;
	return *obj;
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

void GameObject::on_collision(Collider2D* other) {
	for (auto& comp : components) {
		comp.second->on_collision(other);
	}
}

id_t GameObject::get_id() {
	return id;
}

std::string GameObject::get_name() {
	return name;
}

GameScene* GameObject::get_scene() {
	return scene;
}

Transform& GameObject::get_transform() {
	return transform;
}

std::unordered_map<std::type_index, ObjectComponent*>& GameObject::get_components() {
	return components;
}

std::vector<RenderableComponent*>& GameObject::get_renderable_components() {
	return renderable_components;
}