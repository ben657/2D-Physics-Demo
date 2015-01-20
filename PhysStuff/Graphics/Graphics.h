#pragma once

#include <HAPI_lib.h>
#include <map>
#include <unordered_map>
#include <Math/Vec2.h>

struct Colour
{		
	BYTE b = 0;
	BYTE g = 0;
	BYTE r = 0;
	BYTE a = 1;

	Colour(float red = 0.f, float green = 0.f, float blue = 0.f) : r((BYTE)red), b((BYTE)blue), g((BYTE)green)
	{}
};

class Texture;
class Animation;
class Rect;

class Graphics
{
private:
	static Graphics* instance_;

	BYTE* screenPtr_;
	int scrWidth_ = 0;
	int scrHeight_ = 0;
	Colour clearColour_;

	std::unordered_map<std::string, Texture*> textures_;
	std::vector<Animation*> animations_;

protected:
	Graphics();

public:	
	static Graphics* Instance();
 
	~Graphics();	

	void Initialise(int screenWidth, int screenHeight);
	
	int GetScreenWidth(){ return scrWidth_; }
	int GetScreenHeight(){ return scrHeight_; }

	void SetClearColour(float r, float g, float b);
	void Clear();

	void LoadTexture(std::string loadPath, std::string uid);
	void CreateTexture(Colour& colour, int width, int height, std::string uid);

	int CreateAnimation(int startFrame, int endFrame, int frameWidth, int frameHeight, int framesAcross, int framesDown, int fps);
	void UpdateAnimation(const int animID, float delta);

	void Blit(const Vec2& position, const std::string& uid);
	void BlitRect(const Vec2& position, int width, int height, const Colour& colour);
	void BlitAlpha(const Vec2& position, const std::string& uid);
	void BlitAnimated(const Vec2& position, const std::string& texID, const int animID);

	void BlitLine(const Vec2& p1, const Vec2& p2, const Colour& colour);
};

#define gfx Graphics::Instance()

