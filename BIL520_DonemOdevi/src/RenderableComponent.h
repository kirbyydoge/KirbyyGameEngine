#pragma once
#include "ObjectComponent.h"
#include <vector>

class RenderableComponent : public ObjectComponent {
public:
	void bind() const { }
	void unbind() const { }
	virtual void draw() const { }
};