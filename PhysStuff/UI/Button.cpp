#include "Button.h"

Button::Button(int x, int y, int width, int height, const Colour& bgCol, const std::string& text) : UIEntity(x, y), width_(width), height_(height), colour_(bgCol), text_(text)
{
	collider = new RectCollider(width, height);	
	offset_.x_ = width * 0.5f;
	offset_.y_ = height * 0.5f;
}


Button::~Button()
{
}

void Button::Update(float delta)
{
	lastClicked_ = clicked_;
	clicked_ = false;

	if (input->MouseBtnDown(0))
	{
		collider->position_ = position_;
		if (collider->Contains(input->MousePos()))
		{
			clicked_ = true;
		}
	}
}

void Button::Draw()
{
	gfx->BlitRect(position_ - offset_, width_, height_, colour_);
	Vec2 textPos;
	textPos.x_ = position_.x_ - (text_.length() * 6) * 0.5f;
	textPos.y_ = position_.y_ - 6;
	HAPI->RenderText(textPos.x_, textPos.y_, HAPI_TColour(0, 0, 0), text_);
}