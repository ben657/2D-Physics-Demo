#include <HAPI_lib.h>
#include <Graphics/Graphics.h>
#include <World/World.h>

#include "MyScene.h"

void HAPI_Main()
{		
	world->Initialise(1600, 900);

	MyScene* s = new MyScene();

	world->AddScene(s, "MyScene");
	world->SetActiveScene("MyScene");
	world->Start();

	delete world;
	delete gfx;
	delete input;
}