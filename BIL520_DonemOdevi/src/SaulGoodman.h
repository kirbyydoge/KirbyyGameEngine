#pragma once
#include "LiveComponent.h"
#include "GameObject.h"
#include "Sprite.h"
#include "GameTime.h"

class SaulGoodman : public LiveComponent {
public:
	virtual void start() override {
		sprite = get_base()->get_component<Sprite>();
		counter = 0;
	}
	virtual void fixed_update() override {
		counter += GameTime::fixed_delta_time;
		if (counter > change_freq) {
			int cur_tex = sprite->get_active_texture_idx();
			int max_tex = sprite->get_texture_count();
			sprite->set_active_texture_idx((cur_tex + 1) < max_tex ? (cur_tex + 1) : 0);
			counter -= change_freq;
		}
	}
private:
	Sprite* sprite;
	float counter;
	float change_freq = 0.033f;
};