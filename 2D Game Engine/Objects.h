#ifndef OBJECRTS_CLASS_H
#define OBJECRTS_CLASS_H

#include "Misc.h"
#include "GlobalVars.h"

class Platform {

public:

	Point position;
	float height, width, speed;
	Pixel color;

	Platform(Point pos = Point(0, 0), float height = 50.0f, float width = 50.0f,
		float speed = 0.0f, Pixel color = Pixel(255, 255, 255));

	void draw(std::vector <std::vector <Pixel> >& matrix);

};

class Block {

public:

	Point position;
	float height, width, speed;
	Sprite* sprite;
	int spriteIdx;

	Block(Sprite* sprite, Point pos = Point(0, 0), float height = 50.0f, float width = 50.0f, float speed = 0.0f);

	void draw(std::vector <std::vector <Pixel> >& matrix);

};

#endif