#include "stdafx.h"
#include "Image.h"
#include <fstream>
#include <iostream>

Image::Image(int width, int height) : width(width), height(height)
{
	pixels = new Color[width*height];
	Color _default;
	for (int i = 0; i < width*height; i++) {
		pixels[i] = _default;
	}
}

Image::~Image()
{
	delete[] pixels;
}

void Image::setPixel(int x, int y, const Color& color) {
	pixels[getPixelNumber(x, y)] = color;
}

Color Image::getPixel(int x, int y) const {
	return pixels[getPixelNumber(x, y)];
}

int Image::getPixelNumber(int x, int y) const {
	return y * width + x;
}

Vector3 Image::pixelToScreenspace(int x, int y) const {
	return Vector3(x / (float) width * 2 - 1, -y / (float) height * 2 + 1, 0);
}

void Image::exportPPM(const std::string& filepath) const{
	std::ofstream file;

	file.open(filepath, std::ios::out);
	if (!file.is_open()) { 
		std::cout << "Unable to open file\n";
		return;
	}

	file << "P3\n";
	file << width << " " << height << "\n";
	file << "255\n";

	for (int i = 0; i < width*height; i++)
	{
		file << pixels[i].red << " " << pixels[i].green << " " << pixels[i].blue << "\n";
	}

	file.close();
}