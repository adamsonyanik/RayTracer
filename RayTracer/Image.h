#pragma once
#include "Color.h" 
#include <string>
#include "Vector3.h"

class Image
{
public:
	Image(int width, int height);
	~Image();

	void setPixel(int x, int y, const Color& color);
	Color getPixel(int x, int y) const;

	/**
	* Transforms vector from PixelSpace to ScreenSpace
	* ScreenSpace: leftBottomCorner:(-1, -1, 0), rightTopCorner:(1, 1, 0)
	*
	* @param x pixel x coordinate
	* @param y pixel y coordinate
	* @return vector in screenSpace
	*/
	Vector3 pixelToScreenspace(int x, int y) const;

	/**
	* exports image to file in .ppm format, textfile format
	*
	* @param filepath path to export to
	*/
	void exportPPM(const std::string& filepath) const;
private:
	Color* pixels;
	int width;
	int height;

	int getPixelNumber(int x, int y) const;
};

