#ifndef MISC_CLASS_H
#define MISC_CLASS_H

#include "GlobalVars.h"

#include <utility>
#include <Windows.h>
#include <thread>

struct vec2 {

	float x, y;

	vec2(float xp = 0.0f, float yp = 0.0f);

	void normalize();
	void add(vec2& addVector);

};

struct Point {

	float x, y;

	Point(float xp = 0.0f, float yp = 0.0f);

};

bool point_in_square(Point& p1, Point& p2, float minX, float maxX, float minY, float maxY);

bool Collision(Point pos1, float hight1, float width1, Point pos2, float hight2, float width2);

void getGravity(float& yDir);

void getAirFriction(float& xDir);

bool isOnScreen(Point& pos, int width, int height);

#endif 