#pragma once
#include "GameScene.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <mutex>

class GameRenderer {
public:
	static GameRenderer* get_renderer();
	void render_scene(GameScene &scene) const;
	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
private:
	static std::mutex inst_lock;
	static GameRenderer *inst;
	GameRenderer();
	~GameRenderer();
};