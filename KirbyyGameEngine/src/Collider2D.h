#pragma once
#include "ObjectComponent.h"
#include "Bounds2D.h"

enum class Collider2DType {
	BoxCollider2D,
	CircleCollider2D
};

class Collider2D : public ObjectComponent {
public:
	Collider2D(Collider2DType type, Bounds2D* bounds, bool is_trigger, bool is_static);
	~Collider2D();
	Collider2DType get_type();
	void set_trigger(bool is_trigger);
	bool get_trigger();
	bool get_static();
	Bounds2D* get_bounds();
	virtual bool is_colliding(Collider2D* other);
	virtual void on_collision(Collider2D* other);
	static bool collision2D_box_box(Collider2D* obj0, Collider2D* obj1);
	static bool collision2D_circle_circle(Collider2D* obj0, Collider2D* obj1);
	static bool collision2D_box_circle(Collider2D* obj0, Collider2D* obj1);
private:
	bool is_trigger;
	bool is_static;
	Collider2DType type;
	Bounds2D* bounds;
};