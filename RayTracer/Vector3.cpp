#include "stdafx.h"
#include "Vector3.h"
#include <math.h>

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3 Vector3::operator+(const Vector3& vec) const {
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const {
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator*(float scalar) const {
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator*(const Vector3& vec) const {
	return Vector3(x * vec.x, y * vec.y, z * vec.z);
}

bool Vector3::operator== (const Vector3& vec) const {
	return x == vec.x && y == vec.y && z == vec.z;
}

float Vector3::dotProduct(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::crossProduct(const Vector3& a, const Vector3& b) {
	return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float Vector3::magnitude() const {
	return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::normalized() const {
	return *this * (1/magnitude());
}

Vector3 Vector3::reflect(const Vector3& normal) const {
	return *this - (normal * (2 * Vector3::dotProduct(*this, normal)));
}

Vector3 Vector3::saturated() const {
	float newX = x;
	if (x > 1) newX = 1;
	else if (x < 0) newX = 0;

	float newY = y;
	if (y > 1) newY = 1;
	else if (y < 0) newY = 0;

	float newZ = z;
	if (z > 1) newZ = 1;
	else if (z < 0) newZ = 0;

	return Vector3(newX, newY, newZ);
}

float Vector3::getX() const {
	return x;
}

float Vector3::getY() const {
	return y;
}

float Vector3::getZ() const {
	return z;
}

const std::string Vector3::toString() const {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

Vector3 Vector3::parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials) {
	if (line.second.size() >= 3) {
		float params[3];
		for (int i = 0; i < 3; i++) {
			try {
				params[i] = std::stof(line.second[i]);
			}
			catch (std::exception& e) {
				throw std::exception(("Line: " + std::to_string(line.first) + ", Parameter: " + std::to_string(i) + " '" + line.second[i] + "' not a float").c_str());
			}
		}

		return Vector3(params[0], params[1], params[2]);
	}
	else {
		throw std::exception(("Line: " + std::to_string(line.first) + ", Vector3 has not enough paramters : (float x, float y, float z) needed").c_str());
	}
}