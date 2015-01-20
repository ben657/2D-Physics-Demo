#pragma once

#include <Physics/Collider.h>
#include <Math/Math.h>

class RectCollider;

class CircleCollider : public Collider
{
public:
	CircleCollider(int radius);
	~CircleCollider();

	float radius_ = 0.0f;

	std::string GetType() const override { return "circle"; }

	float Left() const { return position_.x_ - radius_; }
	float Right() const { return position_.x_ + radius_; }
	float Top() const { return position_.y_ - radius_; }
	float Bot() const { return position_.y_ + radius_; }

	bool Contains(const Vec2& point) override;

	bool Intersects(PhysEntity* self, PhysEntity* other) override;
	bool IntersectsCircle(PhysEntity* self, PhysEntity* other);
	bool IntersectsRect(PhysEntity* self, PhysEntity* other);

	void Resolve(PhysEntity* self, PhysEntity* other) override;
	void ResolveCircle(PhysEntity* self, PhysEntity* other);
	void ResolveRect(PhysEntity* self, PhysEntity* other);
};