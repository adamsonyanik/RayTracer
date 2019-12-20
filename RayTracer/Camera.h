#pragma once
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(const Vector3& position, const Vector3& rotation, float viewAngleX, float viewAnlgeY);

	/**
	* Transforms vector from ScreenSpace to WorldSpace
	* ScreenSpace: leftBottomCorner:(-1, -1, 0), rightTopCorner:(1, 1, 0)
	*
	* @param vector in ScreenSpace
	* @return ray in WorldSpace
	*/
	Ray screenspaceToRay(const Vector3& vector) const;

	void setPosition(const Vector3& position);
	void setRotation(const Vector3& rotation);

	Vector3 getPosition() const;
	Vector3 getRotation() const;

	/**
	* Parses Camera from Attributes:
	* (Vector3 position, Vector3 rotation, float viewAngleX, float viewAngleY)
	*
	* @param line pair of linenumber and line content, that has camera attributes next
	* @param materials list of materials with associated names
	* @return camera
	*/
	static Camera parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials);
private:
	Vector3 position;
	Vector3 rotation;

	Vector3 rotationMatrixX;
	Vector3 rotationMatrixY;
	Vector3 rotationMatrixZ;

	float viewAngleX;
	float viewAngleY;

	void setRotationMatrix();
};

