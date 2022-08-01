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
	GameObject* player = &GameObject::instantiate_object("Player", glm_ext::new_vec3(0, 0, 0));
	int frame_count = 449;
	Sprite* player_sprite = new Sprite(frame_count);
	for (int i = 0; i < frame_count; i++) {
		player_sprite->set_texture("res/animations/sadabdulhamid/" + std::to_string((i + 1)) + ".jpg", i);
	}
	VertexArray* va = new VertexArray;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	IndexBuffer* ib = new IndexBuffer(indices, 6);
	VertexBufferAttributes vba;
	glm::mat4* projection_matrix = new glm::mat4;
	*projection_matrix = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -1.0f, 1.0f);
	vba.push<float>(2);
	vba.push<float>(2);
	va->add_buffer(*vb, vba);
	player_sprite->set_shader(shader);
	player_sprite->set_vertex_array(va);
	player_sprite->set_index_buffer(ib);
	player_sprite->set_projection(projection_matrix);
	player->add_component<Sprite>(player_sprite);
	player->add_component<PlayerMovement>(new PlayerMovement);
	player->add_component<SaulGoodman>(new SaulGoodman);
	player->add_component<Collider2D>(
		new Collider2D(
			Collider2DType::BoxCollider2D,
			new Box2D(&player->get_transform(), 2.0f, 2.0f),
			false,
			false
		)
	);
	scene->add_object(player);
	scene->add_renderable(player);
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
	GameObject* background = &GameObject::instantiate_object("Background", glm_ext::new_vec3(0, 0, 0));
	int frame_count = 465;
	Sprite* player_sprite = new Sprite(frame_count);
	for (int i = 0; i < frame_count; i++) {
		player_sprite->set_texture("res/animations/3dsaulgoodman/" + std::to_string((i+1)) + ".jpg", i);
	}
	VertexArray* va = new VertexArray;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	IndexBuffer* ib = new IndexBuffer(indices, 6);
	VertexBufferAttributes vba;
	glm::mat4* projection_matrix = new glm::mat4;
	*projection_matrix = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -1.0f, 1.0f);
	vba.push<float>(2);
	vba.push<float>(2);
	va->add_buffer(*vb, vba);
	player_sprite->set_shader(shader);
	player_sprite->set_vertex_array(va);
	player_sprite->set_index_buffer(ib);
	player_sprite->set_projection(projection_matrix);
	background->add_component<Sprite>(player_sprite);
	background->add_component<SaulGoodman>(new SaulGoodman);
	scene->add_object(background);
	scene->add_renderable(background);
	scene->add_live_object(background);
}

void add_wall(BaseScene* scene, glm::vec3 center) {
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
	GameObject* wall = &GameObject::instantiate_object("Wall", center);
	int frame_count = 465;
	Sprite* wall_sprite = new Sprite(frame_count);
	for (int i = 0; i < frame_count; i++) {
		wall_sprite->set_texture("res/animations/3dsaulgoodman/" + std::to_string((i + 1)) + ".jpg", i);
	}
	VertexArray* va = new VertexArray;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	IndexBuffer* ib = new IndexBuffer(indices, 6);
	VertexBufferAttributes vba;
	glm::mat4* projection_matrix = new glm::mat4;
	*projection_matrix = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -1.0f, 1.0f);
	vba.push<float>(2);
	vba.push<float>(2);
	va->add_buffer(*vb, vba);
	wall_sprite->set_shader(shader);
	wall_sprite->set_vertex_array(va);
	wall_sprite->set_index_buffer(ib);
	wall_sprite->set_projection(projection_matrix);
	wall->add_component<Sprite>(wall_sprite);
	wall->add_component<SaulGoodman>(new SaulGoodman);
	wall->add_component<Collider2D>(
		new Collider2D(
			Collider2DType::BoxCollider2D,
			new Box2D(&wall->get_transform(), 2.0f, 2.0f),
			false,
			true
		)
	);
	scene->add_object(wall);
	scene->add_renderable(wall);
	scene->add_live_object(wall);
	scene->add_collider2D(wall->get_component<Collider2D>());
}

void BaseScene::setup() {
	background_setup(this);
	add_wall(this, glm::vec3(-2, -2, 0));
	add_wall(this, glm::vec3(2, -2, 0));
	add_wall(this, glm::vec3(-2, 2, 0));
	add_wall(this, glm::vec3(2, 2, 0));
	player_setup(this);
}
