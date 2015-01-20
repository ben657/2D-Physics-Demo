#include "Input.h"

Input* Input::instance_ = nullptr;

Input* Input::Instance()
{
	if (instance_ == nullptr)
		instance_ = new Input();

	return instance_;
}

Input::Input()
{
}

Input::~Input()
{
	delete kData;	
	delete lastKD;

	delete mData;
	delete lastMD;
	
	for (int i = 0; i < 4; i++)
	{
		delete cData[i];
	}

	delete[] cData;
	delete[] controllers;
}

void Input::Initialise()
{
	kData = new HAPI_TKeyboardData();
	mData = new HAPI_TMouseData();

	cData = new HAPI_TControllerData*[4];
	controllers = new bool[4];
	for (int i = 0; i < 4; i++)
	{
		cData[i] = new HAPI_TControllerData();
		controllers[i] = false;
	}
}

bool Input::KeyDown(const int key)
{
	return kData->scanCode[key];
}

bool Input::KeyJustDown(const int key)
{
	return (!lastKD->scanCode[key] && kData->scanCode[key]);
}

bool Input::KeyJustUp(const int key)
{
	return (lastKD->scanCode[key] && !kData->scanCode[key]);
}

bool Input::MouseBtnDown(const int btn)
{
	switch (btn)
	{
	case 0:
		return mData->leftButtonDown;
		break;
	case 1:
		return mData->rightButtonDown;
		break;
	case 2:
		return mData->middleButtonDown;
		break;
	}
	return false;
}

bool Input::MouseBtnJustDown(const int btn)
{
	switch (btn)
	{
	case 0:
		return (!lastMD->leftButtonDown && mData->leftButtonDown);
		break;
	case 1:
		return (!lastMD->rightButtonDown && mData->rightButtonDown);
		break;
	case 2:
		return (!lastMD->middleButtonDown && mData->middleButtonDown);
		break;
	}
	return false;
}

bool Input::MouseBtnJustUp(const int btn)
{
	switch (btn)
	{
	case 0:
		return (lastMD->leftButtonDown && !mData->leftButtonDown);
		break;
	case 1:
		return (lastMD->rightButtonDown && !mData->rightButtonDown);
		break;
	case 2:
		return (lastMD->middleButtonDown && !mData->middleButtonDown);
		break;
	}
	return false;
}

void Input::Update()
{	
	if (lastKD != nullptr)
		delete lastKD;
	lastKD = kData;
	kData = new HAPI_TKeyboardData();
	HAPI->GetKeyboardData(kData);

	if (lastMD != nullptr)
		delete lastMD;
	lastMD = mData;
	mData = new HAPI_TMouseData();
	HAPI->GetMouseData(mData);
	
	for (int i = 0; i < 4; i++)
	{
		bool active = HAPI->GetControllerData(i, cData[i]);
		controllers[i] = active;
	}
}
