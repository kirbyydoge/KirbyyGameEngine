#include "BaseScene.h"
#include "GameObject.h"
#include "VertexArray.h"
#include "VertexAttribute.h"
#include "IndexBuffer.h"
#include "glm_extended.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Sprite.h"
#include "PlayerMovement.h"
#include "SaulGoodman.h"
#include "Collider2D.h"
#include "Box2D.h"
#include "LineOfSight.h"
#include "Game.h"
#include "GameWindow.h"
#include "Camera.h"

void player_setup(BaseScene* scene) {
	float positions[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	Shader* shader = new Shader("res/shaders/vshader.glsl", "res/shaders/fshader.glsl");
	GameObject* player = &GameObject::instantiate_object(scene, "Player", glm_ext::new_vec3(0, 0, 0));
	int frame_count = 449;
	Sprite* player_sprite = new Sprite(frame_count);
	for (int i = 0; i < frame_count; i++) {
		player_sprite->set_texture("res/animations/sadabdulhamid/" + std::to_string((i + 1)) + ".jpg", i);
	}
	VertexArray* va = new VertexArray;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	IndexBuffer* ib = new IndexBuffer(indices, 6);
	VertexBufferAttributes vba;
	vba.push<float>(2);
	vba.push<float>(2);
	va->add_buffer(*vb, vba);
	player_sprite->set_shader(shader);
	player_sprite->set_vertex_array(va);
	player_sprite->set_index_buffer(ib);
	player_sprite->set_projection(&Camera::proj);
	std::vector<std::pair<std::string, int>> anims;
	anims.push_back(std::make_pair<std::string, int>("res/animations/sadabdulhamid/", 449));
	player->add_component<Sprite>(player_sprite);
	player->add_component<PlayerMovement>(new PlayerMovement);
	player->add_component<SaulGoodman>(new SaulGoodman(anims));
	player->add_component<Collider2D>(
		new Collider2D(
			Collider2DType::BoxCollider2D,
			new Box2D(&player->get_transform(), 2.0f, 2.0f),
			false,
			false
		)
	);
	player->add_component<LineOfSight>(new LineOfSight(
		glm::vec2(1024.0f, 768.0f),
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec2(20.0f, 15.0f)
	));
	scene->add_object(player);
	scene->add_renderable_object(player);
	scene->add_live_object(player);
	scene->add_collider2D(player->get_component<Collider2D>());
}

void background_setup(BaseScene* scene) {
	/*
	float positions[] = {
		-10.0f, -7.5f, 0.0f, 0.0f,
		 10.0f, -7.5f, 1.0f, 0.0f,
		 10.0f,  7.5f, 1.0f, 1.0f,
		-10.0f,  7.5f, 0.0f, 1.0f
	};
	*/
	float positions[] = {
		-10.0f, -7.5f, 0.0f, 0.0f,
		 10.0f, -7.5f, 1.0f, 0.0f,
		 10.0f,  7.5f, 1.0f, 1.0f,
		-10.0f,  7.5f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	Shader* shader = new Shader("res/shaders/vshader.glsl", "res/shaders/fshader.glsl");
	GameObject* background = &GameObject::instantiate_object(scene, "Background", glm_ext::new_vec3(0, 0, 0));
	int frame_count = 465;
	Sprite* player_sprite = new Sprite(frame_count);
	for (int i = 0; i < frame_count; i++) {
		player_sprite->set_texture("res/animations/3dsaulgoodman/" + std::to_string((i+1)) + ".jpg", i);
	}
	VertexArray* va = new VertexArray;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	IndexBuffer* ib = new IndexBuffer(indices, 6);
	VertexBufferAttributes vba;
	vba.push<float>(2);
	vba.push<float>(2);
	va->add_buffer(*vb, vba);
	player_sprite->set_shader(shader);
	player_sprite->set_vertex_array(va);
	player_sprite->set_index_buffer(ib);
	player_sprite->set_projection(&Camera::proj);
	background->add_component<Sprite>(player_sprite);
	scene->add_object(background);
	scene->add_renderable_object(background);
	scene->add_live_object(background);
}

void add_wall(BaseScene* scene, glm::vec3 center) {
	GameObject* wall = &GameObject::instantiate_object(scene, "Wall", center);
	std::vector<std::pair<std::string, int>> anims;
	anims.push_back(std::make_pair<std::string, int>("res/animations/bettercallsaul/", 65));
	anims.push_back(std::make_pair<std::string, int>("res/animations/3dsaulgoodman/", 465));
	wall->add_component<SaulGoodman>(new SaulGoodman(anims));
	wall->add_component<Collider2D>(
		new Collider2D(
			Collider2DType::BoxCollider2D,
			new Box2D(&wall->get_transform(), 2.0f, 2.0f),
			false,
			true
		)
	);
	scene->add_object(wall);
	scene->add_renderable_object(wall);
	scene->add_live_object(wall);
	scene->add_collider2D(wall->get_component<Collider2D>());
}

void BaseScene::setup() {
	//background_setup(this);
	Camera::proj = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -1.0f, 1.0f);
	add_wall(this, glm::vec3(-2, -2, 0));
	add_wall(this, glm::vec3(2, -2, 0));
	add_wall(this, glm::vec3(-2, 2, 0));
	add_wall(this, glm::vec3(2, 2, 0));
	player_setup(this);
}
