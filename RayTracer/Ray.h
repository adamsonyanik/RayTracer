#pragma once
#include "Vector3.h"
#include "Rayhit.h"
#include "Color.h"

class Mesh;

class Ray
{
public:
	Ray(const Vector3& origin, const Vector3& direction);
	Ray(const Vector3& origin, const Vector3& direction, const Vector3& energy);

	Vector3 getOrigin() const;
	Vector3 getDirection() const;

	/**
	* calculates color along ray hits different meshes
	*
	* @param meshes all meshes
	* @param meshesSize number of meshes
	* @param lightDir directional light direction
	* @return color
	*/
	const Color trace(Mesh** meshes, int meshesSize, const Vector3& lightDir);

	/**
	* calculates closest hit
	*
	* @param meshes all meshes
	* @param meshesSize number of meshes
	* @return closest Rayhit to ray origin
	*/
	const Rayhit rayIntersect(Mesh** meshes, int meshesSize) const;

	/**
	* calculates color of a single rayhit
	*
	* @param hit rayhit
	* @param meshes all meshes
	* @param meshesSize number of meshes
	* @param lightDir directional light direction
	* @return color in percentage
	*/
	const Vector3 shade(const Rayhit& hit, Mesh** meshes, int meshesSize, const Vector3& lightDir);
private:
	Vector3 origin;
	Vector3 direction;
	Vector3 energy;
};

