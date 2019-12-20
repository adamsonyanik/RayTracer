#include "stdafx.h"
#include "Sphere.h"
#include <math.h>

Sphere::Sphere() : radius(1) {
	
}

Sphere::Sphere(const Vector3& position, float radius, Material* material) : Mesh(material), position(position), radius(radius)
{
}

const Rayhit Sphere::rayIntersect(const Ray& ray) const {

	// calculate if ray is intersecting with the sphere
	Vector3 distance = ray.getOrigin() - position;
	float p1 = -Vector3::dotProduct(ray.getDirection(), distance);
	float p2sqr = p1 * p1 - Vector3::dotProduct(distance, distance) + radius * radius;
	if (p2sqr < 0)
		return Rayhit::nonHit;

	// calculate distance from origin to hit
	float p2 = (float)sqrt(p2sqr);
	float t = p1 - p2 > 0 ? p1 - p2 : p1 + p2;
	if (t < 0)
		return Rayhit::nonHit;

	Vector3 hitposition = ray.getOrigin() + ray.getDirection() * t;

	return Rayhit(hitposition, t, (hitposition - position).normalized(), material);
}

Sphere* Sphere::parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials) {
	if (line.second.size() < 5) {
		throw std::exception(("Line: " + std::to_string(line.first) + ", Sphere has not enough paramters: (Vector3 position, float radius, Material) needed").c_str());
	}

	float params[4];
	for (int i = 0; i < 4; i++) {
		try {
			params[i] = std::stof(line.second[i]);
		}
		catch (std::exception& e) {
			throw std::exception(("Line: " + std::to_string(line.first) + ", Parameter: " + std::to_string(i) + " '" + line.second[i] + "' not a float").c_str());
		}
	}

	line.second.erase(line.second.begin(), line.second.begin() + 4);
	return new Sphere(Vector3(params[0], params[1], params[2]), params[3], Material::parse(line, materials));
}
