#include "GameRenderer.h"

GameRenderer& GameRenderer::get_renderer() {
	// TODO: This is proven to be not thread-safe. Change implementation later.
	if (inst == nullptr) {
		inst_lock.lock();
		if (inst == nullptr) {
			inst = new GameRenderer();
		}
		inst_lock.unlock();
	}
	return *inst;
}

void GameRenderer::render(const GameScene &scene) {
	
}

GameRenderer::GameRenderer() {
	inst = nullptr;
}

GameRenderer::~GameRenderer() {
	delete inst;
}