#pragma once
#include "Mesh.h"
#include "Rayhit.h"

class Triangle : public Mesh
{
public:
	Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, Material* material);

	virtual const Rayhit rayIntersect(const Ray& ray) const override;

	/**
	* Parses Triangle from Attributes:
	* (Vector3 vertex1, Vector3 vertex2, Vector3 vertex3, Material)
	*
	* @param line pair of linenumber and line content, that has camera attributes next
	* @param materials list of materials with associated names
	* @return triangle
	*/
	static Triangle* parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials);
private:
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;

	Vector3 normal;
	Vector3 invertedNormal;
};

