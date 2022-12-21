#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H

#include "Misc.h"
#include "Objects.h"
#include "GlobalVars.h"

class Enemy {

public:

	Point position;
	float height, width, speed, yDir, airSpeed, ogSpeed;

	float walkableDistance, walkedDistance;

	//vec2 direction;

	int standingIdx, walkingIdx, airIdx;

	Sprite* sprite;

	std::vector<Sprite*> standingSprites;
	std::vector<Sprite*> walkingSprites;
	std::vector<Sprite*> airSprites;

	bool hasSprite;
	bool isMovingX, side;
	bool isActive;

public:

	Enemy(Point pos = Point(0, 0), float walkableDistance = 300.0f, float height = 50.0f, float width = 50.0f,
		bool hasSprite = false, float speed = 100.0f, float airSpeed = 45.0f);

	Point getMovement();

	void fixCollisions(Point& nextPos, std::vector <Platform>& platforms, std::vector <Block*>& blocks);
	void draw(std::vector <std::vector <Pixel> >& matrix);

	void loadSprite(void(*playerSpriteFunc)(Sprite*, std::vector <Sprite*>&,
		std::vector <Sprite*>&, std::vector <Sprite*>&));

	void mainCicle(std::vector <Platform>& platforms, std::vector <Block* >& blocks);

};

#endif