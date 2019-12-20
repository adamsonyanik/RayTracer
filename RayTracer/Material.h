#pragma once
#include "Vector3.h"
#include <vector>
#include <map>

class Material
{
public:
	Material();
	Material(const Vector3& albedo, const Vector3& specular);
	~Material();

	const Vector3 getAlbedo() const;
	const Vector3 getSpecular() const;

	/**
	* Parses Material from Attributes:
	* (Vector3 albedo, Vector3 specular) | materialname
	*
	* @param line pair of linenumber and line content, that has camera attributes next
	* @param materials list of materials with associated names
	* @return material
	*/
	static Material* parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials);
private:
	Vector3 albedo;
	Vector3 specular;
};