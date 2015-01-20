#pragma once
class Rect
{
public:

	int left_ = 0;	
	int right_ = 0;
	int top_ = 0;
	int bottom_ = 0;

	Rect(int left = 0, int top = 0, int width = 0, int height = 0);
	~Rect();

	bool Intersects(const Rect& other);
	void ClipTo(const Rect& other);
	int Width() const;
	int Height() const;
};

