#pragma once

#include <Math/Rect.h>

class Animation
{
private:
	int startFrame_ = 0;
	int endFrame_ = 0;
	int frameWidth_ = 0;
	int frameHeight_ = 0;
	int framesAcross_ = 0;
	int framesDown_ = 0;
	int fps_ = 0;

	float frameTime_ = 0.f;
	float fTimeElapsed_ = 0.f;
	int currentFrame_ = 0;

public:
	Animation(int startFrame, int endFrame, int frameWidth, int frameHeight, int framesAcross, int framesDown, int fps) :
		startFrame_(startFrame), endFrame_(endFrame), frameWidth_(frameWidth), frameHeight_(frameHeight), framesAcross_(framesAcross), framesDown_(framesDown), frameTime_(1000.f/fps), currentFrame_(startFrame) {}
	~Animation(){};

	void Update(float delta);
	Rect GetFrameRect() const;
};

