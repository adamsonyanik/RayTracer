#include "stdafx.h"
#include "GroundPlane.h"
#include <math.h>
#include <iostream>

GroundPlane::GroundPlane() {}

GroundPlane::GroundPlane(Material* material) : Mesh(material)
{}

const Rayhit GroundPlane::rayIntersect(const Ray& ray) const {
	float t = -ray.getOrigin().getY() / ray.getDirection().getY();
	if (t > 0) {
		return Rayhit(ray.getOrigin() + ray.getDirection() * t, t, Vector3(0.0f, 1.0f, 0.0f), material);
	}

	return Rayhit::nonHit;
}

GroundPlane* GroundPlane::parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials) {
	if (line.second.size() < 1) {
		throw std::exception(("Line: " + std::to_string(line.first) + ", GroundPlane has not enough paramters: (Material) needed").c_str());
	}

	return new GroundPlane(Material::parse(line, materials));
}