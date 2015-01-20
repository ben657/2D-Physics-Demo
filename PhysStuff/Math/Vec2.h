#pragma once

#include <math.h>

class Vec2
{	
public:
	static float Distance(const Vec2& v1, const Vec2& v2);
	static float Dot(const Vec2& v1, const Vec2& v2);

	Vec2(float x = 0, float y = 0);
	~Vec2();

	float x_ = 0.f;
	float y_ = 0.f;

	float Length() const;
	float Length2() const;
	void Normalise();
	Vec2 Normalised() const;
	void Zero();

	void operator=(const Vec2& other);
	Vec2 operator+(const Vec2& other) const;
	void operator+=(const Vec2& other);
	Vec2 operator-(const Vec2& other) const;
	void operator-=(const Vec2& other);
	Vec2 operator*(const Vec2& other) const;
	void operator*=(const Vec2& other);
	Vec2 operator*(const float other) const;
	void operator*=(const float other);
	Vec2 operator/(const float other) const;
	void operator/=(const float other);
};

