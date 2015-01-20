#pragma once

#include <algorithm>
#include <World/Scene.h>
#include <World/PhysEntity.h>
#include <Physics/Spring.h>
#include <Physics/CircleCollider.h>
#include <Physics/RectCollider.h>
#include <Input.h>
#include <UI/UI.h>
#include <UI/Button.h>

class MyScene : public Scene
{
private:

	std::vector<Spring*> springs;

	PhysEntity* holding = nullptr;

	PhysEntity* springStart = nullptr;

	PhysEntity* ground = nullptr;
	PhysEntity* leftWall = nullptr;
	PhysEntity* rightWall = nullptr;

	Button* rectCollOn = nullptr;
	Button* circCollOn = nullptr;

	bool mouseCaught = false;
	bool rectColliders = false;

	float currStiffness = 1.f;

	std::string RandomCol();

	void LeftClick(const Vec2& position);
	void RightClick(const Vec2& position);

	void Collisions();

public:
	MyScene();
	~MyScene();

	void AddPhysEntity(int x, int y);
	void AddSpring(PhysEntity* end1, PhysEntity* end2);

	void ChangeStiffness(float amount);

	void Update(float delta) override;
	void FixedUpdate() override;
	void Draw() override;
};

