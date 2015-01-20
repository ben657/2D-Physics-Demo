#pragma once

#include <string>
#include <Math/Math.h>

class PhysEntity;

class Collider
{
public:
	Vec2 position_;

	virtual std::string GetType() const = 0;

	virtual bool Contains(const Vec2& point) = 0;
	//Returns how far this intersects the other collider
	virtual bool Intersects(PhysEntity* self, PhysEntity* other) = 0;
	virtual void Resolve(PhysEntity* self, PhysEntity* other) = 0;
};