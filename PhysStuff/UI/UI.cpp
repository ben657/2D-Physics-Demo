#include "UI.h"

UI* UI::instance_ = nullptr;

UI* UI::Instance()
{
	if (instance_ == nullptr)
		instance_ = new UI();

	return instance_;
}

UI::UI()
{
}


UI::~UI()
{
	for (UIEntity* e : entities_)
	{
		delete e;
	}
}

void UI::Update(float delta)
{
	for (UIEntity* e : entities_)
	{
		e->Update(delta);
	}
}

void UI::Draw()
{
	for (UIEntity * e : entities_)
	{
		e->Draw();
	}
}
