#include "GameRenderer.h"

std::mutex GameRenderer::inst_lock;
GameRenderer* GameRenderer::inst = nullptr;

GameRenderer* GameRenderer::get_renderer() {
	// TODO: This is proven to be not thread-safe. Change implementation later.
	if (inst == nullptr) {
		inst_lock.lock();
		if (inst == nullptr) {
			inst = new GameRenderer();
		}
		inst_lock.unlock();
	}
	return inst;
}

void GameRenderer::render(GameScene& scene) {
	auto renderable_objects = scene.get_renderable_components();
	for (auto obj : renderable_objects) {
		
	}
}

GameRenderer::GameRenderer() {
	inst = nullptr;
}

GameRenderer::~GameRenderer() {
	delete inst;
}