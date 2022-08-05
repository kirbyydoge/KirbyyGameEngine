#include "GameRenderer.h"
#include "GL/glew.h"

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
	for (auto obj : renderable_objects) {
		obj->draw();
	}
	auto& render_once = scene->get_render_once();
	for (auto obj : render_once) {
		obj->draw();
	}
	glfwSwapBuffers(window);
	glfwPollEvents();
	render_once.clear();
}

void GameRenderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
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