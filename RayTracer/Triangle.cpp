#include "stdafx.h"
#include "Triangle.h"


Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, Material* material) : Mesh(material), v1(v1), v2(v2), v3(v3)
{
	normal = Vector3::crossProduct(v2 - v1, v3 - v1).normalized();
	invertedNormal = normal * -1;
}


const Rayhit Triangle::rayIntersect(const Ray& ray) const {
	// egdes from vertex 1 to other verticies
	Vector3 edge1 = v2 - v1;
	Vector3 edge2 = v3 - v1;

	// calculate determinant
	Vector3 pvec = Vector3::crossProduct(ray.getDirection(), edge2);
	float det = Vector3::dotProduct(edge1, pvec);

	// ray parallel to triangle?
	if (det < 1e-8f && det > -1e-8f)
		return Rayhit::nonHit;

	float inv_det = 1.0f / det;
	// distance from vertex 1 to ray origin
	Vector3 tvec = ray.getOrigin() - v1;

	// u, hit coordinate in object space
	float u = Vector3::dotProduct(tvec, pvec) * inv_det;
	if (u < 0.0 || u > 1.0f)
		return Rayhit::nonHit;

	// v, hit coordinate in object space
	Vector3 qvec = Vector3::crossProduct(tvec, edge1);
	float v = Vector3::dotProduct(ray.getDirection(), qvec) * inv_det;

	// u and v need to be >0 and <1, u+v <= 1 to be in bounds of triangle
	if (v < 0.0f || u + v > 1.0f)
		return Rayhit::nonHit;

	// distance along ray
	float t = Vector3::dotProduct(edge2, qvec) * inv_det;
	if (t < 0)
		return Rayhit::nonHit;

	Vector3 hitposition = ray.getOrigin() + ray.getDirection() * t;

	// rendering both sides, so need to return invertedNormal or normal, depending on ray / determinant
	return Rayhit(hitposition, t, (det < 0 ? invertedNormal : normal), material);
}

Triangle* Triangle::parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials) {
	if (line.second.size() < 10) {
		throw std::exception(("Line: " + std::to_string(line.first) + ", Triangle has not enough paramters: (Vector3 vertex1, Vector3 vertex2, Vector3 vertex3, Material) needed").c_str());
	}

	float params[9];
	for (int i = 0; i < 9; i++) {
		try {
			params[i] = std::stof(line.second[i]);
		}
		catch (std::exception& e) {
			throw std::exception(("Line: " + std::to_string(line.first) + ", Parameter: " + std::to_string(i) + " '" + line.second[i] + "' not a float").c_str());
		}
	}

	line.second.erase(line.second.begin(), line.second.begin() + 9);
	return new Triangle(Vector3(params[0], params[1], params[2]), Vector3(params[3], params[4], params[5]), Vector3(params[6], params[7], params[8]), Material::parse(line, materials));
}