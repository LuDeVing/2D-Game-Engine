#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "Misc.h"
#include "Objects.h"
#include "Player.h"
#include "GlobalVars.h"
#include "ParticleSystem.h"
#include "Enemy.h"

#include <vector>
#include <utility>

class Camera {

public:

	float followSpeed;
	Point nextPosition, difference;

	Camera(float followSpeed = 0.5f);

	void follow(Point position, float dy);

	void adjustPosition(Point& pos, float screenWidth, float screenheigh);
	void adjustPosition(std::pair <float, float>& pos, float screenWidth, float screenheight);

	void mainCicle(Player& p1, std::vector<Platform>& platforms, std::vector<Block*>& blocks,
		std::vector<Particles*>& particles, std::vector <Enemy*>& enemies, float screenWidth, float screenheight);

};

#endif