#include "GameTime.h"

float GameTime::_delta_time = 0;
const float& GameTime::delta_time = GameTime::_delta_time;

void GameTime::set_delta_time(float delta_time) {
	_delta_time = delta_time;
}