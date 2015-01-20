#include <World/World.h>

#include <World/Scene.h>
#include <Input.h>

World* World::instance_ = nullptr;

World* World::Instance()
{
	if (instance_ == nullptr)
		instance_ = new World();

	return instance_;
}

World::World()
{
}

World::~World()
{
	for (auto iterator : scenes_)
	{
		delete iterator.second;
	}
}

void World::Initialise(int width, int height)
{	
	gfx->Initialise(width, height);
	gfx->SetClearColour(0.f, 0.f, 0.f);

	input->Initialise();

	HAPI->ChangeFont("Arial", 16, 20);

	lastFrameTime_ = (float)HAPI->GetTime();
	gravity_ = Vec2(0.f, .0098f);
}

void World::Start()
{
	//HAPI->SetShowFPS(true);
	float spareTime = 0.0f;
	while (HAPI->Update())
	{
		frameTime_ = (float)HAPI->GetTime() - lastFrameTime_;
		lastFrameTime_ = (float)HAPI->GetTime();

		spareTime += frameTime_;
						
		while (spareTime > 0.f && doPhysics_)
		{					
			activeScene_->FixedUpdate();
			spareTime -= delta_;	
		}	
		if (!doPhysics_){ spareTime = 0; }

		input->Update();
		activeScene_->Update(frameTime_);
		Draw();		
	}
}

void World::AddScene(Scene* scene, std::string uid)
{
	scenes_[uid] = scene;
}

Scene* World::GetScene(std::string uid)
{
	if (scenes_.find(uid) == scenes_.end())
		return nullptr;
	return scenes_[uid];
}

void World::SetActiveScene(std::string uid)
{
	activeScene_ = scenes_[uid];
}

Scene* World::GetActiveScene()
{
	return activeScene_;
}

void World::Draw()
{
	gfx->Clear();
	activeScene_->Draw();	

	if (doPhysics_)
		HAPI->RenderText(10, 10, HAPI_TColour(255, 0, 0), "Physics: Running");
	else 
		HAPI->RenderText(10, 10, HAPI_TColour(255, 0, 0), "Physics: Paused");	
}
