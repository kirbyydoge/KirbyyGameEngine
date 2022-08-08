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
	float dims = 1.5f;
	std::string path = "res/textures/maincharacter.png";
	GameObject* player = &GameObject::instantiate_object(scene, "Player", glm_ext::new_vec3(0, 0, -0.4f), 
															GameObjectTag::PLAYER);
	player->add_component<PlayerMovement>(new PlayerMovement);
	Sprite* sprite = Sprite::make_sprite(path, dims, dims);
	sprite->set_draw_order(100);
	player->add_component<Sprite>(sprite);
	player->add_component<Collider2D>(
		new Collider2D(
			Collider2DType::BoxCollider2D,
			new Box2D(&player->get_transform(),dims , dims),
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

void target_setup(BaseScene* scene, glm::vec3 center, float dims) {
	std::string path = "res/textures/apple.png";
	GameObject* target = &GameObject::instantiate_object(scene, "Target", center, GameObjectTag::TARGET);
	std::vector<std::pair<std::string, int>> anims;
	Sprite* tg_sprite = Sprite::make_sprite(path, dims, dims);
	target->add_component<Sprite>(tg_sprite);
	target->add_component<Collider2D>(
		new Collider2D(
			Collider2DType::BoxCollider2D,
			new Box2D(&target->get_transform(), dims * 0.6, dims * 0.6),
			false,
			true
		)
	);
	tg_sprite->set_draw_order(10);
	scene->add_object(target);
	scene->add_renderable_object(target);
	scene->add_live_object(target);
	scene->add_collider2D(target->get_component<Collider2D>());
}

void background_setup(BaseScene* scene, glm::vec3 center) {
	std::string path = "res/textures/ground.png";
	GameObject* background = &GameObject::instantiate_object(scene, "Background", center,
									GameObjectTag::UNDEFINED);
	Sprite* bg_sprite = Sprite::make_sprite(path, 20.0f, 16.0f);
	background->add_component<Sprite>(bg_sprite);
	scene->add_object(background);
	scene->add_renderable_object(background);
}

void add_wall(BaseScene* scene, glm::vec3 center, float dims) {
	std::string path = "res/textures/wall.jpg";
	GameObject* wall = &GameObject::instantiate_object(scene, "Wall", center,
															GameObjectTag::OBSTACLE);
	std::vector<std::pair<std::string, int>> anims;
	Sprite* bg_sprite = Sprite::make_sprite(path, dims, dims);
	wall->add_component<Sprite>(bg_sprite);
	wall->add_component<Collider2D>(
		new Collider2D(
			Collider2DType::BoxCollider2D,
			new Box2D(&wall->get_transform(), dims, dims),
			false,
			true
		)
	);
	scene->add_object(wall);
	scene->add_renderable_object(wall);
	scene->add_live_object(wall);
	scene->add_collider2D(wall->get_component<Collider2D>());
}

void make_map(BaseScene* scene, int* map, int dim_x, int dim_y, float width, float height) {
	for (int i = 0; i < dim_y; i++) {
		for (int j = 0; j < dim_x; j++) {
			if (map[i * dim_x + j] == 1) {
				float x = (j - dim_x / 2) * width + width / 2;
				float y = -(i - dim_y / 2) * height - height / 2;
				add_wall(scene, glm::vec3(x, y, 0), width);
			}
			if (map[i * dim_x + j] == 2) {
				float x = (j - dim_x / 2) * width + width / 2;
				float y = -(i - dim_y / 2) * height - height / 2;
				target_setup(scene, glm::vec3(x, y, 0), 1.0f);
			}
		}
	}
}

void BaseScene::setup() {
	Camera::proj = glm::ortho(-10.0f, 10.0f, -8.0f, 8.0f, -1.0f, 1.0f);
	background_setup(this, glm::vec3(0, 0, -0.9f));
	int map[] = {
		1,2,1,0,0,0,0,1,1,0,
		1,0,0,0,1,0,0,0,0,1,
		0,0,0,1,1,1,0,1,0,0,
		0,0,1,0,0,0,0,2,1,0,
		0,1,1,0,0,0,0,1,0,0,
		0,1,0,0,0,0,0,0,0,0,
		0,1,0,1,0,1,1,1,1,0,
		0,0,0,1,0,1,2,0,0,0
	};
	add_wall(this, glm::vec3(-1, -1, 0), 0.5f);
	make_map(this, map, 10, 8, 2.0f, 2.0f);
	player_setup(this);
}
