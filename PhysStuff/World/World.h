#pragma once

#include <map>
#include <string>
#include <time.h>

#include <Math/Vec2.h>
#include <Graphics/Graphics.h>

class Scene;

class World
{
private:
	static World* instance_;

	std::map<std::string, Scene*> scenes_;
	Scene* activeScene_ = nullptr;
	float lastFrameTime_ = 0;
	float frameTime_ = 0;
	float delta_ = 1000.f / 60.f;
	
	bool doPhysics_ = true;

protected:
	World();

public:	
	static World* Instance();
	Vec2 gravity_ = Vec2(0.0f, .0098f);
	~World();

	void Initialise(int width, int height);
	void Start();

	void AddScene(Scene* scene, std::string uid);
	Scene* GetScene(std::string uid);
	void SetActiveScene(std::string uid);
	Scene* GetActiveScene();

	void SetGravity(float gravity) { gravity_ = gravity; }
	Vec2 Gravity() { return gravity_; }
	void SetGravity(const Vec2& gravity){ gravity_ = gravity; }

	void TogglePhysics(){ doPhysics_ = !doPhysics_; }
	bool PhysicsRunning() { return doPhysics_; }

	void Draw();
};

#define world World::Instance()

