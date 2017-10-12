#include "Vector3.h"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


Vector3::~Vector3()
{
}


void Vector3::setVector3(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

int Vector3::getVector3x()
{
	return x;
}

int Vector3::getVector3y()
{
	return y;
}

int Vector3::getVector3z()
{
	return z;
}

Vector3::Vector3(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
