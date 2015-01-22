#include "MyScene.h"

MyScene::MyScene()
{
	gfx->LoadTexture("Data/Images/red.png", "red");
	gfx->LoadTexture("Data/Images/green.png", "green");
	gfx->LoadTexture("Data/Images/blue.png", "blue");

	world->SetGravity(Vec2(0.0f, .18f));

	ground = new PhysEntity(0 + gfx->GetScreenWidth() * 0.5f, 816 + 42, RandomCol());
	ground->SetTag("ball");
	ground->SetCollider(new RectCollider(gfx->GetScreenWidth(), 84));
	ground->SetOffset(Vec2(-16.f, -16.f));
	ground->SetMass(10.f);
	ground->restitution_ = 0.9f;
	ground->Freeze();
	ground->interactive_ = false;
	AddEntity(ground);
	
	leftWall = new PhysEntity(-16, 0, RandomCol());
	leftWall->SetTag("ball");
	leftWall->SetCollider(new RectCollider(32, gfx->GetScreenWidth() * 2));
	leftWall->SetMass(10.f);
	leftWall->SetOffset(Vec2(-16.f, -16.f));
	leftWall->restitution_ = 0.7f;
	leftWall->Freeze();
	leftWall->interactive_ = false;
	AddEntity(leftWall);

	rightWall = new PhysEntity(gfx->GetScreenWidth() + 16, 0, RandomCol());
	rightWall->SetTag("ball");
	rightWall->SetCollider(new RectCollider(32, gfx->GetScreenWidth() * 2));
	rightWall->SetMass(10.f);
	rightWall->SetOffset(Vec2(-16.f, -16.f));
	rightWall->restitution_ = 0.7f;
	rightWall->Freeze();
	rightWall->interactive_ = false;
	AddEntity(rightWall);

	rectCollOn = new Button(745, 100, 100, 50, Colour(255, 0, 0), "Rect Colliders");
	circCollOn = new Button(855, 100, 100, 50, Colour(0, 255, 0), "Circle Colliders");

	ui->AddUIEntity(rectCollOn);
	ui->AddUIEntity(circCollOn);	
}

MyScene::~MyScene()
{
	Scene::~Scene();
	for (int i = 0; i < springs.size(); i++)
	{
		delete springs[i];
	}
}

void MyScene::AddPhysEntity(int x, int y)
{
	//Add a new ball at given position, with default values
	//and a random colour
	PhysEntity* entity = new PhysEntity(x, y, RandomCol());
	entity->SetTag("ball");
	if (rectColliders)
		entity->SetCollider(new RectCollider(32, 32));
	else
		entity->SetCollider(new CircleCollider(16));
	entity->SetOffset(Vec2(-16.f, -16.f));
	entity->SetMass(10.f);
	entity->restitution_ = 0.8f;
	AddEntity(entity);
}

void MyScene::AddSpring(PhysEntity* end1, PhysEntity* end2)
{
	if (end1 == end2)
	{
		springStart = nullptr;
		return;
	}

	//Add a new spring linking the two entities, using the
	//curretn value of spring stiffness
	Spring* spring = new Spring(end1, end2);
	spring->restLength_ = Vec2::Distance(end1->GetPosition(), end2->GetPosition());
	spring->stiffness_ = currStiffness;
	spring->damping_ = .5f;
	springs.push_back(spring);
	springStart = nullptr;
}

void MyScene::ChangeStiffness(float amount)
{
	currStiffness += amount;
	if (currStiffness < 0)
		currStiffness = 0;

	for (int i = 0; i < (int)springs.size(); i++)
	{
		springs[i]->stiffness_ = currStiffness;
	}
}

std::string MyScene::RandomCol()
{
	int r = math::randomBtwn(0, 2);
	return r == 1 ? "red" : "green";
}

void MyScene::LeftClick(const Vec2& position)
{
	for (int i = 0; i < entities_.size(); i++)
	{
		if (entities_[i]->GetTag() != "ball")
			continue;

		//Loop through each ball, if one has been clicked...
		PhysEntity* entity = (PhysEntity*)entities_[i];
		if (entity->interactive_ && entity->GetCollider()->Contains(position))
		{
			if (input->KeyDown(HK_LSHIFT))
			{
				//If we haven't started placing a spring, start at
				//the clicked ball
				if (springStart == nullptr)
					springStart = entity;
				//If we have already started, crate the spring between
				//the first ball and the one just clicked
				else				
					AddSpring(springStart, entity);				
			}
			else if (input->KeyDown(HK_LCONTROL))
			{
				if (entity->IsFrozen())
				{
					//Let it go!
					entity->UnFreeze();
					entity->SetTextureID(RandomCol());
				}
				else
				{
					entity->Freeze();
					entity->SetTextureID("blue");
				}
			}
			else
			{
				holding = entity;
			}
			return;
		}
	}
	//If we didn't hit anything, add a new ball
	AddPhysEntity(position.x_, position.y_);
}

void MyScene::RightClick(const Vec2& position)
{
	for (int i = 0; i < entities_.size(); i++)
	{
		PhysEntity* entity = (PhysEntity*)entities_[i];
		if (entity->interactive_ && entity->GetCollider()->Contains(position))
		{
			//Look for springs attached to the clicked entity and delete them
			//then delete the clicked entity
			for (int i = 0; i < springs.size(); i++)
			{
				Spring* spring = springs[i];
				if (spring->end1_ == entity || spring->end2_ == entity)
				{
					delete springs[i];
					springs.resize(std::remove(springs.begin(), springs.end(), spring) - springs.begin());
					i--;
				}
			}
			delete entity;
			entities_.resize(std::remove(entities_.begin(), entities_.end(), entity) - entities_.begin());
			return;
		}
	}
}

void MyScene::Collisions()
{
	for (Entity* e : entities_)
	{
		if (e->GetTag() != "ball")
			continue;

		PhysEntity* pe = (PhysEntity*)e;
		
		if (pe->IsFrozen())
			continue;

		for (Entity* e2 : entities_)
		{
			if (e2 == e || e2->GetTag() != "ball")
				continue;

			PhysEntity* pe2 = (PhysEntity*)e2;

			if (pe->GetCollider()->Intersects(pe, pe2))
			{
				pe->Collide(pe2);
			}			
		}
	}
}

void MyScene::Update(float delta)
{
	mouseCaught = false;
	ui->Update(delta);	

	if (rectCollOn->justClicked())
	{
		rectCollOn->colour_ = Colour(0, 255, 0);
		circCollOn->colour_ = Colour(255, 0, 0);
		rectColliders = true;
		mouseCaught = true;
	}

	if (circCollOn->justClicked())
	{
		circCollOn->colour_ = Colour(0, 255, 0);
		rectCollOn->colour_ = Colour(255, 0, 0);
		rectColliders = false;
		mouseCaught = true;
	}

	Vec2 mPos = input->MousePos();

	if (input->KeyJustDown(' '))
		world->TogglePhysics();

	if (input->MouseBtnJustDown(0) && !mouseCaught)
	{
		LeftClick(mPos);
	}
	if (input->MouseBtnJustDown(1) && !mouseCaught)
	{
		RightClick(mPos);
	}

	if (input->MouseBtnJustUp(0))
	{
		if (holding != nullptr)
		{
			holding->SetVelocity(input->MouseDelta());
			holding = nullptr;
		}
	}		

	Scene::Update(delta);

	if (holding != nullptr)
	{
		Vec2 delta = input->MouseDelta();
		holding->SetPosition(mPos);
		holding->SetVelocity(input->MouseDelta());
	}
}

void MyScene::FixedUpdate()
{
	Collisions();

	for (int i = 0; i < springs.size(); i++)
	{
		springs[i]->FixedUpdate();
	}		

	Scene::FixedUpdate();	
	if (ground->GetVelocity().x_ != 0.0f || ground->GetVelocity().y_ != 0.0f)
	{
		HAPI->DebugText("this should never run");
	}

	if (holding != nullptr)
	{
		holding->SetVelocity(input->MouseDelta());
	}
}

void MyScene::Draw()
{
	for (int i = 0; i < springs.size(); i++)
	{
		gfx->BlitLine(springs[i]->end1_->GetPosition(), springs[i]->end2_->GetPosition(), Colour(255, 255, 255));
	}
	gfx->BlitLine(Vec2(0, 816), Vec2(1600, 816), Colour(255, 255, 255));	

	HAPI->RenderText(10, 40, HAPI_TColour(255, 0, 0), "Controls:");
	HAPI->RenderText(10, 70, HAPI_TColour(255, 0, 0), "Left click blank space to create a ball");
	HAPI->RenderText(10, 90, HAPI_TColour(255, 0, 0), "Left click a ball to hold and throw it");
	HAPI->RenderText(10, 110, HAPI_TColour(255, 0, 0), "Shift-Left click two balls to connect with a spring");
	HAPI->RenderText(10, 130, HAPI_TColour(255, 0, 0), "Ctrl-Left click a ball to freeze it");
	HAPI->RenderText(10, 150, HAPI_TColour(255, 0, 0), "Right click a ball to remove it and its connections");
	HAPI->RenderText(10, 170, HAPI_TColour(255, 0, 0), "Space to pause physics simulation");
	HAPI->RenderText(10, 190, HAPI_TColour(255, 0, 0), std::string("Will create ") + (rectColliders ? "Rectangle" : "Circle") + " colliders");

	ui->Draw();

	Scene::Draw();
}
