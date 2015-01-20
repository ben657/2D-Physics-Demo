#include "CircleCollider.h"
#include <Physics/RectCollider.h>
#include <World/PhysEntity.h>

CircleCollider::CircleCollider(int radius) : radius_(radius)
{
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::Contains(const Vec2& point)
{
	return (point - position_).Length2() < radius_ * radius_;
}

bool CircleCollider::Intersects(PhysEntity* self, PhysEntity* other)
{
	if (other->GetCollider()->GetType() == "circle")
		return IntersectsCircle(self, other);
	if (other->GetCollider()->GetType() == "rect")
		return IntersectsRect(self, other);
}

bool CircleCollider::IntersectsCircle(PhysEntity* self, PhysEntity* other)
{
	CircleCollider& oColl = *(CircleCollider*)other->GetCollider();
	return ((radius_ + oColl.radius_) * (radius_ + oColl.radius_) - (self->GetPosition() - other->GetPosition()).Length2()) > 0;
}

bool CircleCollider::IntersectsRect(PhysEntity* self, PhysEntity* other)
{
	RectCollider& oColl = *(RectCollider*)other->GetCollider();

	Vec2 closest;
	closest.x_ = math::clampf(position_.x_, oColl.Left(), oColl.Right());
	closest.y_ = math::clampf(position_.y_, oColl.Top(), oColl.Bot());

	return Vec2::Distance(position_, closest) < radius_;
}

void CircleCollider::Resolve(PhysEntity* self, PhysEntity* other)
{
	if (other->GetCollider()->GetType() == "rect")
		ResolveRect(self, other);
	if (other->GetCollider()->GetType() == "circle")
		return ResolveCircle(self, other);
}

void CircleCollider::ResolveCircle(PhysEntity* self, PhysEntity* other)
{
	if (self->IsFrozen())
		return;

	CircleCollider& oColl = *(CircleCollider*)other->GetCollider();
	Vec2 pos = self->GetPosition();
	Vec2 direction = other->GetPosition() - position_;
	Vec2 rVel = other->GetVelocity() - self->GetVelocity();

	direction.Normalise();
	float distance = (radius_ + oColl.radius_) - Vec2::Distance(position_, oColl.position_);

	float r = math::minf(self->restitution_, other->restitution_);
	float tMass = self->GetInvMass() + other->GetInvMass();
	float massMult1 = self->GetInvMass() / tMass;
	float massMult2 = other->GetInvMass() / tMass;

	if (self->IsFrozen() && other->IsFrozen())
	{
		massMult1 = 0.f;
		massMult2 = 0.f;
	}
	else if (self->IsFrozen())
	{
		massMult1 = 0.0f;
		massMult2 = 1.0f;
	}
	else if (other->IsFrozen())
	{
		massMult1 = 1.0f;
		massMult2 = 0.0f;
	}

	Vec2 j = direction * rVel.Length() * Vec2::Dot(rVel.Normalised(), direction) * (1 + r);

	Vec2 vel1 = self->GetVelocity();	
	vel1 += j * massMult1;

	Vec2 vel2 = other->GetVelocity();
	vel2 -= j * massMult2;

	self->SetVelocity(vel1);
	other->SetVelocity(vel2);

	self->SetPosition(pos - direction * distance);
}

void CircleCollider::ResolveRect(PhysEntity* self, PhysEntity* other)
{
	if (self->IsFrozen())
		return;

	RectCollider& oColl = *(RectCollider*)other->GetCollider();
	Vec2 oPos = oColl.position_;

	Vec2 rPos;
	if (position_.x_ < oPos.x_)
	{
		rPos.x_ = Right() - oColl.Left();
	}
	else
	{
		rPos.x_ = oColl.Right() - Left();
	}
	if (position_.y_ < oPos.y_)
	{
		rPos.y_ = Bot() - oColl.Top();
	}
	else
	{
		rPos.y_ = oColl.Bot() - Top();
	}

	if (rPos.x_ < rPos.y_)
	{
		if (position_.x_ > oPos.x_)
		{
			//Move self Right
			position_.x_ += oColl.Right() - Left();
		}
		else
		{
			//Move self Left
			position_.x_ += oColl.Left() - Right();
		}
	}
	else if (rPos.x_ > rPos.y_)
	{
		if (position_.y_ > oPos.y_)
		{
			//Move self up
			position_.y_ += oColl.Bot() - Top();
		}
		else
		{
			//Move self down
			position_.y_ += oColl.Top() - Bot();
		}
	}

	Vec2 closest;
	closest.x_ = math::clampf(position_.x_, oColl.Left(), oColl.Right());
	closest.y_ = math::clampf(position_.y_, oColl.Top(), oColl.Bot());

	Vec2 direction = closest - position_;
	direction.Normalise();

	Vec2 rVel = other->GetVelocity() - self->GetVelocity();

	float r = math::minf(self->restitution_, other->restitution_);
	float tMass = self->GetInvMass() + other->GetInvMass();
	float massMult1 = self->GetInvMass() / tMass;
	float massMult2 = other->GetInvMass() / tMass;

	if (self->IsFrozen() && other->IsFrozen())
	{
		massMult1 = 0.f;
		massMult2 = 0.f;
	}
	else if (self->IsFrozen())
	{
		massMult1 = 0.0f;
		massMult2 = 1.0f;
	}
	else if (other->IsFrozen())
	{
		massMult1 = 1.0f;
		massMult2 = 0.0f;
	}

	float f1 = 1.f - self->friction_;
	float f2 = 1.f - other->friction_;
	
	Vec2 tangent(direction.y_, -direction.x_);
	Vec2 j = direction * rVel.Length() * Vec2::Dot(rVel.Normalised(), direction) * -(1 + r);

	Vec2 vel1 = self->GetVelocity();	
	vel1 -= j * massMult1;
	vel1 += tangent * f1 * rVel.Normalised();
	
	Vec2 vel2 = other->GetVelocity();
	vel2 += j * massMult2;
	vel2 -= tangent * f2 * rVel.Normalised();

	self->SetVelocity(vel1);
	other->SetVelocity(vel2);

	self->SetPosition(position_);
}