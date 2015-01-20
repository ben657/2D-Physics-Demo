#include "PhysEntity.h"


PhysEntity::PhysEntity(int x, int y, std::string textureID) : Entity(x, y, textureID)
{
}

PhysEntity::~PhysEntity()
{
	Entity::~Entity();
	delete collider_;
}

void PhysEntity::SetVelocity(const Vec2& velocity)
{
	if (frozen_)
		return;

	velocity_ = velocity;
}

void PhysEntity::SetVelocityX(const float X)
{
	if (frozen_)
		return;

	velocity_.x_ = X;
}

void PhysEntity::SetVelocityY(const float Y)
{
	if (frozen_)
		return;

	velocity_.y_ = Y;
}

void PhysEntity::AddForce(Vec2& direction, const float magnitude)
{
	direction.Normalise();
	AddForce(direction * magnitude);
}

void PhysEntity::AddForce(const Vec2& force)
{
	if (invMass_ <= 0 || frozen_)
		return;

	velocity_ += force * invMass_;
}

void PhysEntity::Freeze()
{
	frozen_ = true;
}

void PhysEntity::UnFreeze()
{
	frozen_ = false;
}

void PhysEntity::ToggleFreeze()
{
	frozen_ = !frozen_;
}

void PhysEntity::Collide(PhysEntity* other)
{	
	collider_->Resolve(this, other);
}

void PhysEntity::Update(float delta)
{	
	collider_->position_ = position_;
}

void PhysEntity::FixedUpdate()
{	
	collider_->position_ = position_;
	if (!frozen_){
		if (applyGravity_)
		{
			velocity_ += world->Gravity();
		}

		if (velocity_.x_ < 0.05f && velocity_.x_ > -0.05f)
			velocity_.x_ = 0.0f;
		if (velocity_.y_ < 0.05f && velocity_.y_ > -0.05f)
			velocity_.y_ = 0.0f;

		position_ += velocity_;
	}	
}