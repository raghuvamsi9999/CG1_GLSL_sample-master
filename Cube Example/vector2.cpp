#include "Vector2.h"


void Vector2::setVector2(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Vector2::getVector2x()
{
	return x;
}

int Vector2::getVector2y()
{
	return y;
}

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(int x, int y)
{
	this->x = x;
	this->y = y;
}


Vector2::~Vector2()
{
}