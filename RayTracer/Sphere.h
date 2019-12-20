#pragma once
#include "Mesh.h"
#include "Rayhit.h"

class Sphere : public Mesh
{
public:
	Sphere();
	Sphere(const Vector3& position, float radius, Material* material);

	virtual const Rayhit rayIntersect(const Ray& ray) const override;

	/**
	* Parses Sphere from Attributes:
	* (Vector3 position, float radius, Material)
	*
	* @param line pair of linenumber and line content, that has camera attributes next
	* @param materials list of materials with associated names
	* @return sphere
	*/
	static Sphere* parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials);
private:
	Vector3 position;
	float radius;
};