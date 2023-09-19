#pragma once
#include "RenderableComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexAttribute.h"
#include "IndexBuffer.h"
#include "glm/glm.hpp"

class Sprite : public RenderableComponent {
public:
	Sprite(unsigned int tex_count = 1);
	~Sprite();
	static Sprite* make_sprite(std::string& path, float dimx, float dimy);
	static Sprite* make_sprite(std::string& path, int frame_count, float dimx, float dimy);
	void set_projection(glm::mat4* proj);
	void set_shader(Shader* shader);
	Shader& get_shader();
	void set_vertex_array(VertexArray* va);
	VertexArray& get_vertex_array();
	void set_index_buffer(IndexBuffer* ib);
	IndexBuffer& get_index_buffer();
	void set_texture(const std::string& path, unsigned int tex_idx = 0);
	Texture& get_texture(unsigned int tex_idx = 0);
	void bind() const;
	void unbind() const;
	virtual void draw() const override;
	unsigned int get_texture_count() const;
	void set_active_texture_idx(unsigned int index);
	unsigned int get_active_texture_idx() const;
private:
	unsigned int tex_count;
	unsigned int active_text;
	unsigned int active_slot;
	glm::mat4* proj;
	Shader* shader;
	VertexArray* va;
	IndexBuffer* ib;
	Texture* textures;
};