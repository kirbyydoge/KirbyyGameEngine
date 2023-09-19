#include "GameRenderer.h"
#include "GL/glew.h"
#include <algorithm>

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

void GameRenderer::render_scene(GameScene* scene, GLFWwindow* window) const {
	clear();
	auto& renderable_objects = scene->get_renderable_components();
	auto& render_once = scene->get_render_once();
	for (auto obj : renderable_objects) {
		render_once.push_back(obj);
	}
	std::sort(render_once.begin(), render_once.end(),
		[](auto& left, auto& right) {
			return left->get_draw_order() < right->get_draw_order();
	});
	for (auto obj : render_once) {
		if (obj->is_enabled()) {
			obj->draw();
		}
	}
	glfwSwapBuffers(window);
	glfwPollEvents();
	render_once.clear();
}

void GameRenderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GameRenderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	shader.use();
	va.bind();
	ib.bind();
	glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
}

GameRenderer::GameRenderer() {
	inst = nullptr;
}

GameRenderer::~GameRenderer() {
	delete inst;
}