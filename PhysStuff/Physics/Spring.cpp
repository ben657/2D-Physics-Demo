#include "Spring.h"


Spring::Spring(PhysEntity* end1, PhysEntity* end2) : end1_(end1), end2_(end2)
{
}

Spring::~Spring()
{

}

void Spring::FixedUpdate()
{
	Vec2 direction = end1_->GetPosition() - end2_->GetPosition();
	float distance = direction.Length();
	Vec2 relativeV = end1_->GetVelocity() - end2_->GetVelocity();

	Vec2 damping = relativeV * damping_;
	Vec2 force = (direction / distance) * (distance - restLength_) * -stiffness_;

	if (!end1_->IsFrozen())
		end1_->AddForce(force - damping);
	if (!end2_->IsFrozen())
		end2_->AddForce((force * -1.f) + damping);
}