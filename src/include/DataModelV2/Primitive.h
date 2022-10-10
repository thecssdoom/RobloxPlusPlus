#pragma once
#include <G3DAll.h>

class Primitive
{
public:
	Primitive(void);
	float getRadius();

	Vector3 getSize();
	void setSize(Vector3 _size);
private:
	Vector3 size;
};
