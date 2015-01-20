#include "RectCollider.h"
#include <World/PhysEntity.h>

RectCollider::~RectCollider()
{
}

bool RectCollider::Contains(const Vec2& point)
{
	return (point.x_ > Left() && point.x_ < Right() && point.y_ > Top() && point.y_ < Bot());
}

bool RectCollider::Intersects(PhysEntity* self, PhysEntity* other)
{
	if (other->GetCollider()->GetType() == "rect")
		return IntersectsRect(self, other);
	if (other->GetCollider()->GetType() == "circle")
		return IntersectsCircle(self, other);
}

bool RectCollider::IntersectsRect(PhysEntity* self, PhysEntity* other)
{	
	RectCollider& oColl = *(RectCollider*)other->GetCollider();
	return (Left() < oColl.Right() && Right() > oColl.Left()
		&& Top() < oColl.Bot() && Bot() > oColl.Top());
}

bool RectCollider::IntersectsCircle(PhysEntity* self, PhysEntity* other)
{
	return false;
}

void RectCollider::Resolve(PhysEntity* self, PhysEntity* other)
{
	if (other->GetCollider()->GetType() == "rect")
		ResolveRect(self, other);
	else if (other->GetCollider()->GetType() == "circle")
		ResolveCircle(self, other);
}

void RectCollider::ResolveCircle(PhysEntity* self, PhysEntity* other)
{
	//Don't do anything, let the circle do it
}

void RectCollider::ResolveRect(PhysEntity* self, PhysEntity* other)
{
	if (self->IsFrozen())
		return;

	Vec2 pos = self->GetPosition();
	Vec2 oPos = other->GetPosition();
	Vec2 rPos;

	Vec2 rVel = other->GetVelocity() - self->GetVelocity();

	RectCollider& oColl = *(RectCollider*)other->GetCollider();

	Vec2 finalVel;

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

	if (pos.x_ < oPos.x_)
	{
		rPos.x_ = Right() - oColl.Left();
	}
	else
	{
		rPos.x_ = oColl.Right() - Left();
	}
	if (pos.y_ < oPos.y_)
	{
		rPos.y_ = Bot() - oColl.Top();
	}
	else
	{
		rPos.y_ = oColl.Bot() - Top();
	}

	float f1 = 1.f - self->friction_;
	float f2 = 1.f - other->friction_;

	if (rPos.x_ < rPos.y_)
	{
		if (pos.x_ > oPos.x_)
		{
			//Move self Right
			pos.x_ += oColl.Right() - Left();
			self->SetVelocity(Vec2(-rVel.x_ * massMult1 * r, -rVel.y_ * f1));
			other->SetVelocity(Vec2(rVel.x_ * massMult2 * r, rVel.y_ * f2));
		}
		else
		{
			//Move self Left
			pos.x_ += oColl.Left() - Right();
			self->SetVelocity(Vec2(rVel.x_ * massMult1 * r, -rVel.y_  * f1));
			other->SetVelocity(Vec2(-rVel.x_ * massMult2 * r, rVel.y_ * f2));
		}		
	}
	else if (rPos.x_ > rPos.y_)
	{
		if (pos.y_ > oPos.y_)
		{
			//Move self up
			pos.y_ += oColl.Bot() - Top();
			self->SetVelocity(Vec2(-rVel.x_ * f1, -rVel.y_ * massMult1 * r));
			other->SetVelocity(Vec2(rVel.x_ * f2, rVel.y_ * massMult2 * r));
		}
		else
		{
			//Move self down
			pos.y_ += oColl.Top() - Bot();
			self->SetVelocity(Vec2(-rVel.x_ * f1, rVel.y_ * massMult1 * r));
			other->SetVelocity(Vec2(rVel.x_ * f2, -rVel.y_ * massMult2 * r));
		}
	} 

	self->SetPosition(pos);
}