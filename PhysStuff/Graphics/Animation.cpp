#include "Animation.h"

void Animation::Update(float delta)
{
	fTimeElapsed_ += delta;

	if (fTimeElapsed_ >= frameTime_)
	{
		currentFrame_++;
		if (currentFrame_ > endFrame_)
			currentFrame_ = startFrame_;

		fTimeElapsed_ = 0.f;
	}
}

Rect Animation::GetFrameRect() const
{
	int frameX = currentFrame_ % framesAcross_;
	int frameY = currentFrame_ / framesAcross_;
	return Rect(frameX * frameWidth_, frameY * frameHeight_, frameWidth_, frameHeight_);
}
 