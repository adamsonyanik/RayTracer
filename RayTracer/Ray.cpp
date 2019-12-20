#include "stdafx.h"
#include "Ray.h"
#include "Mesh.h"
#include "Sphere.h"
#include <iostream>

Ray::Ray(const Vector3& origin, const Vector3& direction) : origin(origin), direction(direction), energy(Vector3(1,1,1))
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction, const Vector3& energy) : origin(origin), direction(direction), energy(energy)
{
}

Vector3 Ray::getOrigin() const {
	return origin;
}

Vector3 Ray::getDirection() const {
	return direction;
}

const Color Ray::trace(Mesh** meshes, int meshesSize, const Vector3& lightDir) {
	Vector3 color;
	// trace 8 reflections
	for (int i = 0; i < 8; i++) {
		Rayhit hit = rayIntersect(meshes, meshesSize);

		color = color + energy * shade(hit, meshes, meshesSize, lightDir);

		// no energy left
		if (hit == Rayhit::nonHit || energy.magnitude() <= 0) {
			break;
		}

		// reflect ray
		energy = energy * hit.getMaterial()->getSpecular();
		origin = hit.getPosition() + hit.getNormal() * 0.001f;
		direction = direction.reflect(hit.getNormal());
	}
	color = color.saturated();
	
	return Color(color.getX() * 255, color.getY() * 255, color.getZ() * 255);
}

const Rayhit Ray::rayIntersect(Mesh** meshes, int meshesSize) const {
	Rayhit closest;

	// get closest hit
	for (int meshIndex = 0; meshIndex < meshesSize; meshIndex++) {
		Rayhit hit = meshes[meshIndex]->rayIntersect(*this);
		if (hit.getDistance() < closest.getDistance()) {
			closest = hit;
		}
	}

	return closest;
}

const Vector3 Ray::shade(const Rayhit& hit, Mesh** meshes, int meshesSize, const Vector3& lightDir) {
	if (hit == Rayhit::nonHit) {
		return getDirection();
	}
	else {
		// position in shadow?
		bool notInShadow = Ray(hit.getPosition() + hit.getNormal() * 0.001f, lightDir * -1)
			.rayIntersect(meshes, meshesSize)
			== Rayhit::nonHit;
		//shadowRay hit nothing
		if (!notInShadow)
		{
			return Vector3(0.0f, 0.0f, 0.0f);
		}

		float diffuse = (Vector3::dotProduct(hit.getNormal(), lightDir) * -1);

		// clamp diffuse to 0-1
		if (diffuse > 1) diffuse = 1;
		else if (diffuse < 0) diffuse = 0;

		return hit.getMaterial()->getAlbedo() * diffuse;
	}
}