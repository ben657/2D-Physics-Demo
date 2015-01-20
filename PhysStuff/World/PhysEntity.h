#pragma once

#include <World/Entity.h>
#include <Physics/Collider.h>

class PhysEntity : public Entity
{
protected:
	Vec2 velocity_;	
	bool frozen_ = false;
	bool applyGravity_ = true;	
	Collider* collider_ = nullptr;
	float invMass_ = 1.f;

public:	
	float restitution_ = 1.f;
	float friction_ = 0.2f;
	bool interactive_ = true;

	PhysEntity(int x = 0, int y = 0, std::string textureID = "");
	virtual ~PhysEntity();

	Collider* GetCollider() { return collider_; }
	void SetCollider(Collider* collider) { collider_ = collider; collider_->position_ = position_; }
	void Collide(PhysEntity* other);

	Vec2 GetVelocity(){ return velocity_; }
	void SetVelocity(const Vec2& velocity);
	void SetVelocityX(const float X);
	void SetVelocityY(const float Y);

	void SetMass(float mass){
		if (mass <= 0){ invMass_ = 0; }
		invMass_ = 1.f / mass;
	}
	float GetInvMass(){ return invMass_; }

	void AddForce(Vec2& direction, const float magnitude);
	void AddForce(const Vec2& force);
	void Freeze();
	void UnFreeze();
	void ToggleFreeze();
	bool IsFrozen(){ return frozen_; }

	void Update(float delta) override;
	void FixedUpdate() override;
};

