#include "stdafx.h"
#include "Image.h"
#include <iostream>
#include "Camera.h"
#include "Mesh.h"
#include "Sphere.h"
#include "GroundPlane.h"
#include "Triangle.h"
#include "MeshLoader.h"

int main() {
	std::string scene = "scenes/test.scene";
	std::string output = "images/test.ppm";

	int outputWidth = 500;
	int outputHeight = 500;

	// load scene
	Camera camera;
	camera.setPosition(Vector3(0, 1, 0));

	Vector3 directionalLight(0, -1, 0);

	Material** material = nullptr;
	int materialSize;
	int meshesSize;
	Mesh** meshes = MeshLoader::loadMeshes(meshesSize, material, materialSize, camera, directionalLight, scene);
	if (meshes == nullptr) {
		system("pause");
		return 1;
	}
	directionalLight = directionalLight.normalized();

	// render to image
	Image* image = new Image(outputWidth, outputHeight);
	for (int x = 0; x < outputWidth; x++) {
		for (int y = 0; y < outputHeight; y++) {
			Ray pixelRay = camera.screenspaceToRay(image->pixelToScreenspace(x, y));

			image->setPixel(x, y, pixelRay.trace(meshes, meshesSize, directionalLight));
		}

		std::cout << (x+1)/(float)outputWidth * 100 << "%\n";
	}

	// delete materials and meshes
	for (int i = 0; i < materialSize; i++) {
		delete material[i];
	}
	delete[] material;

	for (int i = 0; i < meshesSize; i++) {
		delete meshes[i];
	}
	delete[] meshes;

	std::cout << "finished raytracing\nexporting...\n";

	// export image in ppm format
	image->exportPPM(output);

	delete image;

	system("pause");
	return 0;
}