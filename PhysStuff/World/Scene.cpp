#include "Scene.h"

#include <World/Entity.h>

Scene::Scene()
{
}


Scene::~Scene()
{
	for (int i = 0; i < entities_.size(); i++)
	{
		delete entities_[i];
	}
}

int Scene::AddEntity(Entity* entity)
{
	entities_.push_back(entity);
	return entities_.size() - 1;
}

void Scene::Update(float delta)
{
	for (unsigned int i = 0; i < entities_.size(); i++)
		entities_[i]->Update(delta);
}

void Scene::FixedUpdate()
{
	for (unsigned int i = 0; i < entities_.size(); i++)
		entities_[i]->FixedUpdate();
}

void Scene::Draw()
{
	for (unsigned int i = 0; i < entities_.size(); i++)
		entities_[i]->Draw();
}
