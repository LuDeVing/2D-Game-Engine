#include "Objects.h"

Platform::Platform(Point pos, float height, float width, float speed, Pixel color) {

	this->position = pos;
	this->height = height;
	this->width = width;
	this->speed = speed;
	this->color = color;

}

void Platform::draw(std::vector <std::vector <Pixel> >& matrix) {

	Point startPoint;
	Point finalPoint;

	startPoint.x = (position.x - width / 2);
	startPoint.y = (position.y + height / 2);

	finalPoint.x = (position.x + width / 2);
	finalPoint.y = (position.y - height / 2);

	for (int y = startPoint.y; y >= finalPoint.y; y--) {
		for (int x = startPoint.x; x <= finalPoint.x; x++) {

			if (y < 0 || y >= matrix.size()) continue;
			if (x < 0 || x >= matrix[y].size()) continue;

			matrix[y][x] = color;

		}
	}

}

Block::Block(Sprite* sprite, Point pos, float height, float width, float speed) {

	this->position = pos;
	this->height = height;
	this->width = width;
	this->speed = speed;
	this->sprite = sprite;
	this->spriteIdx = 0;

}

void Block::draw(std::vector <std::vector <Pixel> >& matrix) {

	Point startPoint;
	Point finalPoint;

	float width1 = width;
	float height1 = height;

	startPoint.x = (position.x - width1 / 2);
	startPoint.y = (position.y + height1 / 2);

	finalPoint.x = (position.x + width1 / 2);
	finalPoint.y = (position.y - height1 / 2);


	float xB = 0.0f, yB = 0.0f, dx, dy;

	dx = sprite->width / (float)width1;
	dy = sprite->height / (float)height1;


	for (int y = (int)finalPoint.y; y <= (int)startPoint.y; y++) {

		xB = 0.0f;

		if (y < 0 || y >= matrix.size()) {
			yB += dy;
			continue;
		}

		for (int x = (int)startPoint.x; x <= (int)finalPoint.x; x++) {

			if (x < 0 || x >= matrix[y].size()) {
				xB += dx;
				continue;
			}

			if (sprite->GetPixel(floorf(xB), floorf(yB)).a != 0)
				matrix[y][x] = sprite->GetPixel(floorf(xB), floorf(yB));

			xB += dx;

		}

		yB += dy;

	}

}
