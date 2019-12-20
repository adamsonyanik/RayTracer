#pragma once
#include "Vector3.h"
#include "Material.h"

class Rayhit
{
public:
	Rayhit();
	Rayhit(const Vector3& position, float distance, const Vector3& normal, Material* material);
	~Rayhit();

	bool operator== (const Rayhit& other) const;

	const static Rayhit nonHit;

	const Vector3 getPosition() const;
	float getDistance() const;
	const Vector3 getNormal() const;
	const Material* getMaterial() const;
private:
	Vector3 position;
	float distance;
	Vector3 normal;
	Material* material;
};