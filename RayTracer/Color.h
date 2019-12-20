#pragma once
#include "Vector3.h"

class Color
{
public:
	int red;
	int green;
	int blue;

	Color();
	Color(int red, int green, int blue);

	static Color vectorToColor(const Vector3& vector);
};