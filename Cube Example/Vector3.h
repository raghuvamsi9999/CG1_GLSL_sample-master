#pragma once
class Vector3
{
public:
	void setVector3(int x, int y, int z);
	int getVector3x();
	int getVector3y();
	int getVector3z();
	Vector3();
	Vector3(int x, int y, int z);

	~Vector3();
private:
	int x, y, z;
};

