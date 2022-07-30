#include "GameTime.h"

float GameTime::_delta_time = 0;
float GameTime::_fixed_delta_time = 0;
const float& GameTime::delta_time = GameTime::_delta_time;
const float& GameTime::fixed_delta_time = GameTime::_fixed_delta_time;

void GameTime::set_delta_time(float delta_time) {
	_delta_time = delta_time;
}

void GameTime::set_fixed_delta_time(float fixed_delta_time) {
	_fixed_delta_time = fixed_delta_time;
}
