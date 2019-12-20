#pragma once
#include <string> 
#include <vector>
#include <map>

class Material;

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	/**
	* adds each component with the corresponding in the other vector
	*/
	Vector3 operator+ (const Vector3& vec) const;
	/**
	* subtracts each component with the corresponding in the other vector
	*/
	Vector3 operator- (const Vector3& vec) const;
	/**
	* multiplies each component with the scalar
	*/
	Vector3 operator* (float scalar) const;
	/**
	* multiplies each component with the corresponding in the other vector,
	* not a dotProduct
	*/
	Vector3 operator* (const Vector3& vec) const;
	bool operator== (const Vector3& vec) const;

	static float dotProduct(const Vector3& a, const Vector3& b);
	static Vector3 crossProduct(const Vector3& a, const Vector3& b);

	float getX() const;
	float getY() const;
	float getZ() const;

	float magnitude() const;
	Vector3 normalized() const;
	Vector3 reflect(const Vector3& normal) const;
	Vector3 saturated() const;

	const std::string toString() const;

	/**
	* Parses Vector3 from Attributes:
	* (float x, float y, float z)
	*
	* @param line pair of linenumber and line content, that has camera attributes next
	* @param materials list of materials with associated names
	* @return vector3
	*/
	static Vector3 parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials);
private:
	float x;
	float y;
	float z;
};

