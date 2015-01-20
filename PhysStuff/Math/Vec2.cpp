#include "Vec2.h"

float Vec2::Distance(const Vec2& v1, const Vec2& v2)
{
	Vec2 diff = v2 - v1;
	return diff.Length();
}

float Vec2::Dot(const Vec2& v1, const Vec2& v2)
{
	return (v1.x_ * v2.x_) + (v1.y_ * v2.y_);
}

Vec2::Vec2(float x, float y) : x_(x), y_(y)
{
}


Vec2::~Vec2()
{
}

float Vec2::Length() const
{
	return sqrtf((x_ * x_) + (y_ * y_));
}

float Vec2::Length2() const
{
	return (x_ * x_) + (y_ * y_);
}

void Vec2::Normalise()
{
	float length = Length();
	if (length == 0.f)
	{
		x_ = 0.f;
		y_ = 0.f;
		return;
	}
	x_ = x_ / length;
	y_ = y_ / length;
}

Vec2 Vec2::Normalised() const
{
	float length = Length();
	if (length == 0.f)
	{
		return Vec2(0.f, 0.f);
	}
	return Vec2(x_ / length, y_ / length);
}

void Vec2::Zero()
{
	x_ = 0.f;
	y_ = 0.f;
}

void Vec2::operator=(const Vec2& other)
{
	x_ = other.x_;
	y_ = other.y_;
}

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2(x_ + other.x_, y_ + other.y_);
}

void Vec2::operator+=(const Vec2& other)
{
	x_ += other.x_;
	y_ += other.y_;
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return Vec2(x_ - other.x_, y_ - other.y_);
}

void Vec2::operator-=(const Vec2& other)
{
	x_ -= other.x_;
	y_ -= other.y_;
}

Vec2 Vec2::operator*(const Vec2& other) const
{
	return Vec2(x_ * other.x_, y_ * other.y_);
}

void Vec2::operator*=(const Vec2& other)
{
	x_ *= other.x_;
	y_ *= other.y_;
}

Vec2 Vec2::operator*(const float other) const
{
	return Vec2(x_ * other, y_ * other);
}

void Vec2::operator*=(const float other)
{
	x_ *= other;
	y_ *= other;
}

Vec2 Vec2::operator/(const float other) const
{
	return Vec2(x_ / other, y_ / other);
}

void Vec2::operator/=(const float other)
{
	x_ /= other;
	y_ /= other;
}