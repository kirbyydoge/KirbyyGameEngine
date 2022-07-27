#pragma once
#include "GameScene.h"
#include <mutex>

class GameRenderer {
public:
	static GameRenderer& get_renderer();
	void render(const GameScene &scene);
private:
	static std::mutex inst_lock;
	static GameRenderer *inst;
	GameRenderer();
	~GameRenderer();
};