#pragma once
#include "ObjectComponent.h"

class LiveComponent : public ObjectComponent {
public:
	LiveComponent() {}
	~LiveComponent() {}
	virtual void fixed_update() {}
	virtual void early_update() {}
	virtual void update() {}
	virtual void late_update() {}
};