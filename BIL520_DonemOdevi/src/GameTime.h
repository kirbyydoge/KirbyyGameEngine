#pragma once

class GameTime {
public:
	GameTime() = delete;
	~GameTime() = delete;
private:
	static float _delta_time;
	static float _fixed_delta_time;
public:
	static void set_delta_time(float delta_time);
	static void set_fixed_delta_time(float fixed_delta_time);
	static const float& delta_time;
	static const float& fixed_delta_time;
};