#pragma once

class ObjectComponent {
public:
	ObjectComponent() {}
	~ObjectComponent() {}
	
	virtual void start() {}
	virtual void stop() {}
	virtual void fixed_update() {}
	virtual void early_update() {}
	virtual void update() {}
	virtual void late_update() {}
};