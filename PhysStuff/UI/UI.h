#pragma once

#include <UI/UIEntity.h>
#include <vector>

class UI
{
private:
	static UI* instance_;

	std::vector<UIEntity*> entities_;

public:
	static UI* Instance();

	UI();
	~UI();

	void AddUIEntity(UIEntity* e){ entities_.push_back(e); }

	void Update(float delta);
	void Draw();
};

#define ui UI::Instance()