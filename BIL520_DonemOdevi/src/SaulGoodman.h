#pragma once
#include "LiveComponent.h"
#include "GameObject.h"
#include "Sprite.h"
#include "GameTime.h"
#include "Camera.h"

class SaulGoodman : public LiveComponent {
public:
	SaulGoodman(std::vector<std::pair<std::string, int>> anims, float dims) {
		this->anims = anims;
		this->dims = dims;
	}
	virtual void start() override {
		base = this->get_base();
		scene = base->get_scene();
		active_sprite = -1;
		sprites = new Sprite*[anims.size()];
		for (int i = 0; i < anims.size(); i++) {
			std::pair<std::string, int> anim = anims[i];
			std::string name = anim.first;
			int frame_count = anim.second;
			sprites[i] = Sprite::make_sprite(name, frame_count, dims, dims);
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
	float dims;
	std::vector<std::pair<std::string, int>> anims;
	GameObject* base;
	GameScene* scene;
	Sprite** sprites;
	int active_sprite;
	float counter;
	float change_freq = 0.033f;
};