#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(Material* material) : material(material)
{
}

Mesh::~Mesh()
{
}

const Rayhit Mesh::rayIntersect(const Ray& ray) const {
	return Rayhit::nonHit;
}

Mesh* Mesh::parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material>& materials) {
	throw std::exception(("Line: " + std::to_string(line.first) + ", Mesh not parseable").c_str());
}

const Material* Mesh::getMaterial() const {
	return material;
}