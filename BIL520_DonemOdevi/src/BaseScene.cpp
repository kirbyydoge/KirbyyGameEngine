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
	scene->add_object(player);
	scene->add_renderable(player);
	scene->add_live_object(player);
}

void background_setup(BaseScene* scene) {
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

void BaseScene::setup() {
	background_setup(this);
	player_setup(this);
}
