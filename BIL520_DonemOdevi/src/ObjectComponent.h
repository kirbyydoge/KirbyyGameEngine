#pragma once
class GameObject;

class ObjectComponent {
public:
	ObjectComponent() : base(nullptr) {}
	~ObjectComponent() {}
	void set_base(GameObject* base) { this->base = base; }
	GameObject* get_base() { return base; }
	virtual void start() {}
	virtual void stop() {}
protected:
	GameObject* base;
};