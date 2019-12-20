#include "stdafx.h"
#include "Material.h"

#include <iostream>

Material::Material()
{
}

Material::Material(const Vector3& albedo, const Vector3& specular) : albedo(albedo), specular(specular)
{
}


Material::~Material()
{
}

Material* Material::parse(std::pair<int, std::vector<std::string>>& line, std::map<std::string, Material*>& materials) {
	if (line.second.size() >= 1) {
		if (materials.count(line.second.front()) > 0) {
			return materials[line.second[0]];
		}

		if (line.second.size() >= 6) {
			float params[6];
			for (int i = 0; i < 6; i++) {
				try {
					params[i] = std::stof(line.second[i]);
				}
				catch (std::exception& e) {
					throw std::exception(("Line: " + std::to_string(line.first) + ", Parameter: " + std::to_string(i) + " '" + line.second[i] + "' not a float").c_str());
				}
			}

			line.second.erase(line.second.begin(), line.second.begin()+6);
			return new Material(Vector3(params[0], params[1], params[2]), Vector3(params[3], params[4], params[5]));
		}
		else {
			throw std::exception(("Line: " + std::to_string(line.first) + ", Materialname '" + line.second[0] + "' not found").c_str());
		}	
	}
	else {
		throw std::exception(("Line: " + std::to_string(line.first) + ", Material has not enough paramters: (Vector3 albedo, Vector3 specular) needed").c_str());
	}
}

const Vector3 Material::getAlbedo() const {
	return albedo;
}

const Vector3 Material::getSpecular() const {
	return specular;
}