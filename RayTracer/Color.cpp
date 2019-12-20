#include "stdafx.h"
#include "Color.h"

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue) {}

Color Color::vectorToColor(const Vector3& vector) {
	return Color((vector.getX() + 1) * 127, (vector.getY() + 1) * 127, (vector.getZ() + 1) * 127);
}