#pragma once
#include "Ray.h"
#include "Rayhit.h"
#include "Material.h"
#include <vector>
#include <map>

class Mesh
{
public:
	Mesh();
	Mesh(Material* material);
	virtual ~Mesh();

	/**
	* calculates intersection with ray and mesh
	*
	* @param ray that is cast
	*/
	virtual const Rayhit rayIntersect(const Ray& ray) const;

	/**
	* Parses Mesh from Attributes
	*
	* @param line pair of linenumber and line content, that has camera attributes next
	* @param materials list of materials with associated names
	* @return mesh
	*/
	static Mesh* parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material>& materials);

	virtual const Material* getMaterial() const;
protected:
	Material* material;
};