#pragma once
class Vector2
{
public:
	void setVector2(int x, int y);
	int getVector2x();
	int getVector2y();
	Vector2();
	Vector2(int x, int y);
	~Vector2();
private:
	int x, y;
};