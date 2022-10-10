
#include <G3DAll.h>
#include "DataModelV2/Primitive.h"

Primitive::Primitive(void)
{
	size = Vector3(1,1,1);
}

Vector3 Primitive::getSize() 
{	return size;	}

void Primitive::setSize(Vector3 _size) 
{	size = _size;	}

float Primitive::getRadius() {
	float largest = size.x;

	if (size.y > largest) { largest = size.y; 
		if (size.z > largest) { largest = size.z; } 
	}

	return largest;
}