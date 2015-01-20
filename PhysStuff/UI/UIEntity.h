#pragma once

#include <World/Entity.h>

class UIEntity : public Entity
{
public:
	UIEntity(int x, int y);
	~UIEntity();

	virtual void Update(float delta) override{};
	virtual void Draw() override{};
};

