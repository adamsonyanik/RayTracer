#include "stdafx.h"
#include "MeshLoader.h"
#include <fstream>
#include <iostream>
#include "GroundPlane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "assert.h"

Mesh** MeshLoader::loadMeshes(int& meshesSize, Material**& materials, int& materialSize, Camera& camera, Vector3& directionalLight, const std::string& filepath) {
	std::map<int, std::vector<std::string>> file = loadFile(filepath);

	std::map<std::string, Material*> materialList;
	std::vector<Material*> differentMaterials;
	int cameraCount = 0;
	int directionalLightCount = 0;

	for (std::pair<int, std::vector<std::string>> line : file) {
		try {
			if (line.second.front() == "Material") {
				if (line.second.size() < 2) {
					throw std::exception(("Line: " + std::to_string(line.first) + ", Material has no name parameter").c_str());
				}

				// parse material
				std::string materialName = line.second[1];

				line.second.erase(line.second.begin(), line.second.begin()+2);
				materialList[materialName] = Material::parse(line, materialList);

				// push material in differentList
				bool alreadyInList = false;
				for (Material* mat : differentMaterials) {
					if (mat = materialList[materialName]) {
						alreadyInList = true;
						break;
					}
				}
				if (!alreadyInList) {
					differentMaterials.push_back(materialList[materialName]);
				}
			}
			else if (line.second.front() == "Camera") {
				if (cameraCount == 1) {
					throw std::exception(("Line: " + std::to_string(line.first) + ", Camera already defined").c_str());
				}

				// parse camera
				line.second.erase(line.second.begin());
				camera = Camera::parse(line, materialList);
				cameraCount++;
			}
			else if (line.second.front() == "DirectionalLight") {
				if (directionalLightCount == 1) {
					throw std::exception(("Line: " + std::to_string(line.first) + ", DirectionalLight already defined").c_str());
				}

				// parse directionallight
				line.second.erase(line.second.begin());
				directionalLight = Vector3::parse(line, materialList);
				directionalLightCount++;
			}
		}
		catch (const std::exception& e) {
			std::cout << "Exception: " << e.what() << "\n";

			for (Material* mat : differentMaterials) {
				delete mat;
			}

			return nullptr;
		}
	}

	// store Materials in Array
	materialSize = differentMaterials.size();	
	materials = new Material*[materialSize];
	int materialsCounter = 0;
	for (Material* mat: differentMaterials) {
		materials[materialsCounter] = mat;
		materialsCounter++;
	}

	// parse and stor meshes
	meshesSize = file.size() - materialList.size() - cameraCount - directionalLightCount;
	int meshesActualSize = 0;
	Mesh** meshes = new Mesh*[meshesSize];
	try {
		for (std::pair<int, std::vector<std::string>> line : file) {
			if (line.second.front() == "GroundPlane") {
				line.second.erase(line.second.begin());
				meshes[meshesActualSize] = GroundPlane::parse(line, materialList);
				meshesActualSize++;
			}
			else if (line.second.front() == "Sphere"){
				line.second.erase(line.second.begin());
				meshes[meshesActualSize] = Sphere::parse(line, materialList);
				meshesActualSize++;
			}
			else if (line.second.front() == "Triangle"){
				line.second.erase(line.second.begin());
				meshes[meshesActualSize] = Triangle::parse(line, materialList);
				meshesActualSize++;
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << "Exception in '" << filepath << "': " << e.what() << "\n";

		for (int i = 0; i < materialSize; i++) {
			delete materials[i];
		}
		delete[] materials;

		for (int i = 0; i < meshesActualSize; i++) {
			delete meshes[i];
		}
		delete[] meshes;

		return nullptr;
	}

	assert(meshesActualSize == meshesSize);

	return meshes;
}

std::map<int, std::vector<std::string>> MeshLoader::loadFile(const std::string& filepath) {
	std::ifstream file;

	file.open(filepath, std::ios::in);
	if (!file.is_open()) {
		std::cout << "Unable to open file\n";
		return std::map<int, std::vector<std::string>>();
	}

	std::map<int, std::vector<std::string>> fileContent;
	std::string line;
	int linecounter = 0;
	while (std::getline(file, line))
	{
		std::string firstWord = line.substr(0, line.find_first_of(" \t\r\n"));
		if (firstWord == "GroundPlane"
			|| firstWord == "Sphere"
			|| firstWord == "Triangle"
			|| firstWord == "Material"
			|| firstWord == "Camera"
			|| firstWord == "DirectionalLight") {

			// split line into words and store them into words list
			std::vector<std::string> words;

			int wordEndIndex = 0;
			std::string word;

			while (line.length() > 0) {
				wordEndIndex = line.find_first_of(" \t\r\n");
				if (wordEndIndex != -1) {
					word = line.substr(0, wordEndIndex);
					line = line.substr(wordEndIndex + 1, line.length() - wordEndIndex);
				}
				else {
					word = line;
					line = "";
				}

				words.push_back(word);
			}

			// add list to array
			fileContent[linecounter+1] = words;
		}
		// comment
		else if (firstWord == "#" || firstWord == "") {

		}
		// not recognized linestart
		else {
			std::cout << "Warning in '" << filepath << "': Line " << linecounter << ": could not read Line, that is not a Comment. Comments starts with '# '" <<"\n";
		}

		linecounter++;
	}

	file.close();
	return fileContent;
}
