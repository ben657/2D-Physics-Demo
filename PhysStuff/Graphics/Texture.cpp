#include "Texture.h"
#include <iostream>
Texture::Texture(int width, int height) : width_(width), height_(height)
{
	data_ = new BYTE[width * height * 4];
}

Texture::Texture(std::string loadPath)
{
	LoadFromFile(loadPath);
}

Texture::~Texture()
{
//	if (data_ != nullptr)
		delete[] data_;
}

bool Texture::LoadFromFile(std::string loadPath)
{
	HAPI->LoadTexture(loadPath, &data_, &width_, &height_);
	return true;
}

void Texture::Fill(const Colour& colour)
{
	for (int i = 0; i < width_ * height_ * 4; i += 4)
	{
		memcpy(data_ + i, &colour, 4);
	}
}

void Texture::Blit(const Vec2& position, BYTE* screenPtr, const Rect& screenRect)
{
	BYTE* screenOffset = screenPtr;

	int texByteWidth = width_ << 2;
	for (int tY = 0; tY < height_; tY++)
	{
		memcpy(screenOffset, data_ + texByteWidth * tY, texByteWidth);
		screenOffset += width_ * 4;
	}
}

void Texture::BlitAlpha(const Vec2& position, BYTE* screenPtr, const Rect& screenRect)
{
	Rect texRect((int)position.x_, (int)position.y_, width_, height_);

	if (!texRect.Intersects(screenRect))
		return;

	texRect.ClipTo(screenRect);

	BYTE* scrOffset = screenPtr + (texRect.left_ + texRect.top_ * screenRect.Width()) * 4;
	BYTE* texOffset = data_ + ((texRect.left_ - (int)position.x_) + (texRect.top_ - (int)position.y_) * width_) * 4;

	int lineJump = (screenRect.Width() - texRect.Width()) * 4;
	int texJump = (width_ - texRect.Width()) * 4;

	//For each pixel in the texture, multiply it by its alpha, then the pixel at the same place on the screen
	//Then copy the final value in.
	for (int ty = 0; ty < texRect.Height(); ty++)
	{
		for (int tx = 0; tx < texRect.Width(); tx++)
		{
			BYTE a = texOffset[3];

			if (a == 255)
			{
				memcpy(scrOffset, texOffset, 4);
			}
			else if (a > 0)
			{
				scrOffset[0] = scrOffset[0] + ((a * (texOffset[0] - scrOffset[0])) >> 8);
				scrOffset[1] = scrOffset[1] + ((a * (texOffset[1] - scrOffset[1])) >> 8);
				scrOffset[2] = scrOffset[2] + ((a * (texOffset[2] - scrOffset[2])) >> 8);
			}

			texOffset += 4;
			scrOffset += 4;
		}
		texOffset += texJump;
		scrOffset += lineJump;
	}
}

void Texture::BlitAnimated(const Vec2& position, BYTE* screenPtr, const Rect& screenRect, Animation* animation)
{
	Rect frame = animation->GetFrameRect();

	Rect texRect((int)position.x_, (int)position.y_, frame.Width(), frame.Height());

	if (!texRect.Intersects(screenRect))
		return;

	texRect.ClipTo(screenRect);

	BYTE* scrOffset = screenPtr + (texRect.left_ + texRect.top_ * screenRect.Width()) * 4;
	BYTE* texOffset = data_ + (((texRect.left_ - (int)position.x_) + frame.left_) + ((texRect.top_ - (int)position.y_) + frame.top_) * width_) * 4;

	int lineJump = (screenRect.Width() - texRect.Width()) * 4;
	int texJump = (width_ - texRect.Width()) * 4;

	//For each pixel in the texture, multiply it by its alpha, then the pixel at the same place on the screen
	//Then copy the final value in.
	for (int ty = 0; ty < texRect.Height(); ty++)
	{
		for (int tx = 0; tx < texRect.Width(); tx++)
		{
			BYTE a = texOffset[3];

			if (a == 255)
			{
				memcpy(scrOffset, texOffset, 4);
			}
			else if (a > 0)
			{
				scrOffset[0] = scrOffset[0] + ((a * (texOffset[0] - scrOffset[0])) >> 8);
				scrOffset[1] = scrOffset[1] + ((a * (texOffset[1] - scrOffset[1])) >> 8);
				scrOffset[2] = scrOffset[2] + ((a * (texOffset[2] - scrOffset[2])) >> 8);
			}
 
			texOffset += 4;
			scrOffset += 4;
		}
		texOffset += texJump;
		scrOffset += lineJump;
	}
}
