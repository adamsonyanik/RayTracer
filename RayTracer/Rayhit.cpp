#include "stdafx.h"
#include "Rayhit.h"
#include <limits>

Rayhit::Rayhit() : distance(std::numeric_limits<float>::max()) {}

Rayhit::Rayhit(const Vector3& position, float distance, const Vector3& normal, Material* material) : position(position), distance(distance), normal(normal), material(material)
{
}

Rayhit::~Rayhit()
{
}

const Rayhit Rayhit::nonHit;

bool Rayhit::operator== (const Rayhit& other) const {
	return position == other.position && distance == other.distance && normal == other.normal;
}

const Vector3 Rayhit::getPosition() const {
	return position;
}

float Rayhit::getDistance() const {
	return distance;
}

const Vector3 Rayhit::getNormal() const {
	return normal;
}

const Material* Rayhit::getMaterial() const {
	return material;
}