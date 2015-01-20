#pragma once

#include <string>
#include <HAPI_lib.h>
#include <Graphics/Graphics.h>
#include <Graphics/Animation.h>
#include <Math/Vec2.h>
#include <Math/Rect.h>

class Texture
{
private:
	int width_ = 0;
	int height_ = 0;

	BYTE* data_ = nullptr;

public:
	Texture(int width = 0, int height = 0);
	Texture(std::string loadPath);
	~Texture();

	bool LoadFromFile(std::string loadPath);
	void Fill(const Colour& colour);

	int Width() const { return width_; }
	int Height() const { return height_; }
	BYTE* Data() const { return data_; }

	void Blit(const Vec2& position, BYTE* screenPtr, const Rect& screenRect);
	void BlitAlpha(const Vec2& position, BYTE* screenPtr, const Rect& screenRect);
	void BlitAnimated(const Vec2& position, BYTE* screenPtr, const Rect& screenRect, Animation* animation);
};