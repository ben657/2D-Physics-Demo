#include <Graphics/Graphics.h>

#include <Graphics/Texture.h>
#include <Graphics/Animation.h>
#include <Math/Rect.h>

Graphics* Graphics::instance_ = nullptr;

Graphics* Graphics::Instance()
{
	if (instance_ == nullptr)
		instance_ = new Graphics();

	return instance_;
}

Graphics::Graphics()
{	

}

Graphics::~Graphics()
{
	for (auto iterator : textures_)
	{
		delete iterator.second;
	}

	for (Animation* animation : animations_)
	{
		delete animation;
	}
}

void Graphics::Initialise(int screenWidth, int screenHeight)
{
	scrWidth_ = screenWidth;
	scrHeight_ = screenHeight;

	if (!HAPI->Initialise(&scrWidth_, &scrHeight_))
		return;

	screenPtr_ = HAPI->GetScreenPointer();	
}

void Graphics::LoadTexture(std::string loadPath, std::string uid)
{
	Texture* texture = new Texture(loadPath);
	textures_[uid] = texture;
}

void Graphics::CreateTexture(Colour& colour, int width, int height, std::string uid)
{
	Texture* texture = new Texture(width, height);
	texture->Fill(colour);
}

int Graphics::CreateAnimation(int startFrame, int endFrame, int frameWidth, int frameHeight, int framesAcross, int framesDown, int fps)
{
	Animation* a = new Animation(startFrame, endFrame, frameWidth, frameHeight, framesAcross, framesDown, fps);
	animations_.push_back(a);
	return animations_.size() - 1;
}

void Graphics::UpdateAnimation(const int animID, float delta)
{
	if (animID == -1)
		return;
	animations_[animID]->Update(delta);
}

void Graphics::SetClearColour(float r, float g, float b)
{
	clearColour_.r = (BYTE)r;
	clearColour_.g = (BYTE)g;
	clearColour_.b = (BYTE)b;
}

void Graphics::Clear()
{
	if (clearColour_.r == clearColour_.g && clearColour_.r == clearColour_.b)
	{
		memset(screenPtr_, clearColour_.r, (scrWidth_ * scrHeight_) << 2);
	}
	else
	{
		for (int offset = 0; offset < scrWidth_ * scrHeight_; offset++)
		{
			memcpy(screenPtr_ + offset * 4, &clearColour_, 4);
		}
	}
}

void Graphics::Blit(const Vec2& position, const std::string& uid)
{
	if (textures_.find(uid) == textures_.end())
		return;

	Texture* texture = textures_[uid];
	Rect screenRect(0, 0, scrWidth_, scrHeight_);
	texture->Blit(position, screenPtr_, screenRect);
}

void Graphics::BlitRect(const Vec2& position, int width, int height, const Colour& colour)
{
	int lineJump = (scrWidth_ - width) * 4;
	BYTE* currPos = screenPtr_ + ((int)position.x_ + (int)position.y_ * scrWidth_) * 4;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			memcpy(currPos, &colour, 4);
			currPos += 4;
		}
		currPos += lineJump;
	}
}

void Graphics::BlitAlpha(const Vec2& position, const std::string& uid)
{
	if (textures_.find(uid) == textures_.end())
		return;

	Texture* texture = textures_[uid];
	Rect screenRect(0, 0, scrWidth_, scrHeight_);
	texture->BlitAlpha(position, screenPtr_, screenRect);
}

void Graphics::BlitAnimated(const Vec2& position, const std::string& texID, const int animID)
{
	if (textures_.find(texID) == textures_.end())
		return;

	Animation* animation = animations_[animID];

	Texture* texture = textures_[texID];
	Rect screenRect(0, 0, scrWidth_, scrHeight_);
	texture->BlitAnimated(position, screenPtr_, screenRect, animation);
}

void Graphics::BlitLine(const Vec2& p1, const Vec2& p2, const Colour& colour) // adam wishes to know why -.-
{
	int x1 = p1.x_;
	int y1 = p1.y_;
	int x2 = p2.x_;
	int y2 = p2.y_;

	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs((float)dx);
	dy1 = fabs((float)dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		if (x > 0 && x < scrWidth_ && y > 0 && y < scrHeight_)
		{
			BYTE* offset = screenPtr_ + (x + y * scrWidth_) * 4;
			memcpy(offset, &colour, 4);
		}
		for (i = 0; x<xe; i++)
		{
			x = x + 1;
			if (px<0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			if (x > 0 && x < scrWidth_ && y > 0 && y < scrHeight_)
			{
				BYTE* offset = screenPtr_ + (x + y * scrWidth_) * 4;
				memcpy(offset, &colour, 4);
			}
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		if (x > 0 && x < scrWidth_ && y > 0 && y < scrHeight_)
		{
			BYTE* offset = screenPtr_ + (x + y * scrWidth_) * 4;
			memcpy(offset, &colour, 4);
		}
		for (i = 0; y<ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			if (x > 0 && x < scrWidth_ && y > 0 && y < scrHeight_)
			{
				BYTE* offset = screenPtr_ + (x + y * scrWidth_) * 4;
				memcpy(offset, &colour, 4);
			}
		}
	}
}