#pragma once

#include <vector>
#include <World/Entity.h>

class Scene
{
protected:
	Scene();

	std::vector<Entity*> entities_;

public:	
	virtual ~Scene();
	
	int AddEntity(Entity* entity);

	virtual void Update(float delta);
	virtual void FixedUpdate();
	virtual void Draw();
};

