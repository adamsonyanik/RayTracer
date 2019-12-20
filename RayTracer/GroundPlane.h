#pragma once
#include "Mesh.h"
#include "Rayhit.h"

class GroundPlane : public Mesh
{
public:
	GroundPlane();
	GroundPlane(Material* material);

	virtual const Rayhit rayIntersect(const Ray& ray) const override;

	/**
	* Parses GroundPlane from Attributes:
	* (Material)
	*
	* @param line pair of linenumber and line content, that has camera attributes next
	* @param materials list of materials with associated names
	* @return groundPlane
	*/
	static GroundPlane* parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials);
};