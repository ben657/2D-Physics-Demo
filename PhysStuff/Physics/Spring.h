#pragma once

#include <World/PhysEntity.h>

class Spring
{
private:
	

public:
	PhysEntity* end1_;
	PhysEntity* end2_;
	float stiffness_ = 1.f;
	float damping_ = 0.5f;
	float restLength_ = 10.f;

	Spring(PhysEntity* end1, PhysEntity* end2);
	~Spring();

	void FixedUpdate();
};

