#pragma once
#include "LiveComponent.h"
#include "GameObject.h"
#include "Sprite.h"
#include "GameTime.h"
#include "Camera.h"

class SaulGoodman : public LiveComponent {
public:
	SaulGoodman(std::vector<std::pair<std::string, int>> anims) {
		this->anims = anims;
	}
	virtual void start() override {
		base = this->get_base();
		scene = base->get_scene();
		active_sprite = -1;
		sprites = new Sprite*[anims.size()];
		for (int i = 0; i < anims.size(); i++) {
			std::pair<std::string, int> anim = anims[i];
			sprites[i] = make_sprite(anim.first, anim.second);
		}
		set_sprite(0);
	}
	virtual void fixed_update() override {
		counter += GameTime::fixed_delta_time;
		if (counter > change_freq) {
			int cur_tex = sprites[active_sprite]->get_active_texture_idx();
			int max_tex = sprites[active_sprite]->get_texture_count();
			sprites[active_sprite]->set_active_texture_idx((cur_tex + 1) < max_tex ? (cur_tex + 1) : 0);
			counter -= change_freq;
		}
	}
	void set_sprite(int idx) {
		if (idx == active_sprite) {
			return;
		}
		if (active_sprite > -1) {
			scene->delete_renderable_component(sprites[active_sprite]);
		}
		base->add_component<Sprite>(sprites[idx]);
		scene->add_renderable_component(sprites[idx]);
		active_sprite = idx;
		counter = 0;
	}
private:
	std::vector<std::pair<std::string, int>> anims;
	GameObject* base;
	GameScene* scene;
	Sprite** sprites;
	int active_sprite;
	float counter;
	float change_freq = 0.033f;

	Sprite* make_sprite(std::string path, int frame_count) {
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
		base = this->get_base();
		Shader* shader = new Shader("res/shaders/vshader.glsl", "res/shaders/fshader.glsl");
		Sprite* sprite = new Sprite(frame_count);
		for (int i = 0; i < frame_count; i++) {
			sprite->set_texture(path + std::to_string((i + 1)) + ".jpg", i);
		}
		VertexArray* va = new VertexArray;
		VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
		IndexBuffer* ib = new IndexBuffer(indices, 6);
		VertexBufferAttributes vba;
		vba.push<float>(2);
		vba.push<float>(2);
		va->add_buffer(*vb, vba);
		sprite->set_shader(shader);
		sprite->set_vertex_array(va);
		sprite->set_index_buffer(ib);
		sprite->set_projection(&Camera::proj);
		return sprite;
	}
};