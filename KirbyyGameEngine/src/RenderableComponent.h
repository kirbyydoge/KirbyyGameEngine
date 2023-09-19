#pragma once
#include "ObjectComponent.h"
#include <vector>

class RenderableComponent : public ObjectComponent {
public:
	RenderableComponent() { draw_order = 1; }
	void bind() const { }
	void unbind() const { }
	virtual void draw() const { }
	int get_draw_order() { return draw_order; }
	void set_draw_order(int draw_order) { this->draw_order = draw_order; }
private:
	int draw_order;
};