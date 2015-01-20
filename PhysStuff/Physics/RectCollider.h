
#pragma once

#include <Physics/Collider.h>

class CircleCollider;

class RectCollider : public Collider
{
public:
	RectCollider(int width, int height) : width_(width), height_(height){};
	~RectCollider();

	float width_ = 0.0f;
	float height_ = 0.0f;

	float Left() const { return position_.x_ + width_ * -0.5f; }
	float Right() const { return position_.x_ + width_ * 0.5f; }
	float Top() const { return position_.y_ + height_ * -0.5f; }
	float Bot() const { return position_.y_ + height_ * 0.5f; }

	std::string GetType() const override { return "rect"; }

	bool Contains(const Vec2& point) override;

	bool Intersects(PhysEntity* self, PhysEntity* other) override;
	bool IntersectsRect(PhysEntity* self, PhysEntity* other);
	bool IntersectsCircle(PhysEntity* self, PhysEntity* other);

	void Resolve(PhysEntity* self, PhysEntity* other) override;
	void ResolveRect(PhysEntity* self, PhysEntity* other);
	void ResolveCircle(PhysEntity* self, PhysEntity* other);
};