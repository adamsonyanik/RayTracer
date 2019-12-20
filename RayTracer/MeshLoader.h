#pragma once
#include <string>
#include <vector>
#include <map>
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

class MeshLoader
{
public:
	/**
	* loads scenefile
	* 
	* @param meshesSize *out* number of meshes
	* @param materials *out* materialarray with all different materials
	* @param materialSize *out* number of materials
	* @param camera *out* camera from scene
	* @param directionalLight *out* directionalLight from scene
	* @param filepath scenefile path
	* @return meshesarray
	*/
	static Mesh** loadMeshes(int& meshesSize, Material**& materials, int& materialSize, Camera& camera, Vector3& directionalLight, const std::string& filepath);
private:
	/**
	* extracs all relevant line from scenefile
	*
	* @param filepath scenefile path
	* @return list of linenumber and splitted list, into attributes
	*/
	static std::map<int, std::vector<std::string>> loadFile(const std::string& filepath);
};