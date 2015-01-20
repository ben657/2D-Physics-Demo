#include "Math.h"

namespace math
{

	int clamp(int v, int min, int max)
	{
		if (v < min)
			return min;
		if (v > max)
			return max;
		return v;
	}

	float clampf(float v, float min, float max)
	{
		if (v < min)
			return min;
		if (v > max)
			return max;
		return v;
	}

	int closest(int v, int v1, int v2)
	{
		if (math::abs(v - v1) < math::abs(v - v2))
			return v1;
		return v2;
	}

	float closestf(float v, float v1, float v2)
	{
		if (math::absf(v - v1) < math::absf(v - v2))
			return v1;
		return v2;
	}

	int abs(int v)
	{
		if (v < 0)
			return v * -1;
		return v;
	}

	float absf(float v)
	{
		if (v < 0.f)
			return v * -1.f;
		return v;
	}

	int min(int v, int v2)
	{
		return (v < v2) ? v : v2;
	}
	
	float minf(float v, float v2)
	{
		return (v < v2) ? v : v2;
	}
	
	int max(int v, int v2)
	{
		return (v > v2) ? v : v2;
	}
	
	float maxf(float v, float v2)
	{
		return (v > v2) ? v : v2;
	}

	void seedRandom(unsigned int seed)
	{
		srand(seed);
	}

	int random()
	{
		return rand();
	}

	int randomBtwn(int min, int max)
	{
		return min + (rand() % (max - min));
	}
}