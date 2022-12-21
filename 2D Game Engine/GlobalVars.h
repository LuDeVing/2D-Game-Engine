#ifndef GLOBALS_HEADER_H
#define GLOBALS_HEADER_H

#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "Headers/stb_image.h"

class Pixel {

public:

	unsigned int r, g, b, a;

	Pixel(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0, unsigned int a = 255);

};

class DisplayImage {

public:

	unsigned char* imageData;
	unsigned int width, height;

	DisplayImage();
	DisplayImage(unsigned int width, unsigned int height);

	void Draw(int x, int y, Pixel color, unsigned int pixelSize = 1);

};


class Sprite {

private:

	std::vector <std::vector <Pixel> > image;

public:

	int width, height, channels;

	Sprite();
	Sprite(const char* filePath);

	Pixel GetPixel(unsigned int x, unsigned int y);

};

class GlobalVars {

public:

	float deltaTime;
	float AirFriction;
	float GravityStrengh;

	int screenWidth;
	int screenHeight;

	int fullScreenWidth;
	int fullScreenHeight;

	unsigned int blockType;

	std::pair <float, float> position;
	std::map <std::pair <int, int>, bool> mp;
	std::vector <Sprite*> BlockSprites;

	GlobalVars();

};

inline GlobalVars globalvar;

#endif