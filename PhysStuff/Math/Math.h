#pragma once

#include <stdlib.h>
#include <Math/Vec2.h>
#include <Math/Rect.h>

namespace math
{
	int clamp(int v, int min, int max);
	float clampf(float v, float min, float max);

	int closest(int v, int v1, int v2);
	float closestf(float v, float v1, float v2);

	int abs(int v);
	float absf(float v);

	int min(int v, int v2);
	float minf(float v, float v2);
	int max(int v, int v2);
	float maxf(float v, float v2);
	
	void seedRandom(unsigned int seed);
	int random();
	int randomBtwn(int min, int max);
}