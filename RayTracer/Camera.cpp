#include "stdafx.h"
#include "Camera.h"
#include <math.h>
#include <iostream>

float degreeToRadians = 0.01745329251f; // pi/180

Camera::Camera() : viewAngleX(60), viewAngleY(60)
{
	setRotationMatrix();
}

Camera::Camera(const Vector3& position, const Vector3& rotation, float viewAngleX, float viewAngleY) : position(position), rotation(rotation), viewAngleX(viewAngleX), viewAngleY(viewAngleY)
{
	setRotationMatrix();
}

Ray Camera::screenspaceToRay(const Vector3& vector) const {
	float angleX = vector.getX() * sin(viewAngleX * degreeToRadians);
	float angleY = vector.getY() * sin(viewAngleY * degreeToRadians);

	Vector3 dir(angleX, angleY, 1);

	// multiply with rotationmatrix
	Vector3 dirRotated(Vector3::dotProduct(dir, rotationMatrixX), Vector3::dotProduct(dir, rotationMatrixY), Vector3::dotProduct(dir, rotationMatrixZ));
	return Ray(position, dirRotated.normalized());
}

Camera Camera::parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials) {
	if (line.second.size() >= 8) {
		float params[8];
		for (int i = 0; i < 8; i++) {
			try {
				params[i] = std::stof(line.second[i]);
			}
			catch (std::exception& e) {
				throw std::exception(("Line: " + std::to_string(line.first) + ", Parameter: " + std::to_string(i) + " '" + line.second[i] + "' not a float").c_str());
			}
		}

		return Camera(Vector3(params[0], params[1], params[2]), Vector3(params[3], params[4], params[5]), params[6], params[7]);
	}
	else {
		throw std::exception(("Line: " + std::to_string(line.first) + ", Camera has not enough paramters: (Vector3 position, Vector3 rotation, float viewAngleX, float viewAngleY) needed").c_str());
	}
}

void Camera::setPosition(const Vector3& pos) {
	position = pos;
}

void Camera::setRotation(const Vector3& rot) {
	rotation = rot;
	setRotationMatrix();
}

void Camera::setRotationMatrix() {
	float sinA = sin(rotation.getX() * degreeToRadians);
	float cosA = cos(rotation.getX() * degreeToRadians);

	float sinB = sin(rotation.getY() * degreeToRadians);
	float cosB = cos(rotation.getY() * degreeToRadians);

	float sinC = sin(rotation.getZ() * degreeToRadians);
	float cosC = cos(rotation.getZ() * degreeToRadians);

	rotationMatrixX = Vector3(cosC*cosB, cosC*sinB*sinA + -sinC * cosA, cosC*sinB*cosA + -sinC * -sinA);
	rotationMatrixY = Vector3(sinC*cosB, sinC*sinB*sinA + cosC * cosA, sinC*sinB*cosA + cosC * -sinA);
	rotationMatrixZ = Vector3(-sinB, cosB*sinA, cosB*cosA);
}

Vector3 Camera::getPosition() const {
	return position;
}

Vector3 Camera::getRotation() const {
	return rotation;
}