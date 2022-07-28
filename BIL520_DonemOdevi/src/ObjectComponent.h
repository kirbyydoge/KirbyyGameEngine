#pragma once

class ObjectComponent {
public:
	ObjectComponent() {}
	~ObjectComponent() {}
	virtual void start() {}
	virtual void stop() {}
};