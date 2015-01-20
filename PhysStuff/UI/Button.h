#pragma once

#include <Input.h>
#include <UI/UIEntity.h>
#include <Physics/RectCollider.h>

class Button : public UIEntity
{
private:
	RectCollider* collider;
	
	bool lastClicked_ = false;
	bool clicked_ = true;

	Vec2 offset_;	
	int width_ = 0;
	int height_ = 0;
	std::string text_ = "";

public:
	Colour colour_;

	Button(int x, int y, int width, int height, const Colour& bgCol, const std::string& text);
	~Button();

	bool justClicked(){ return clicked_ == true && lastClicked_ == false; }

	void Update(float delta) override;
	void Draw() override;
};