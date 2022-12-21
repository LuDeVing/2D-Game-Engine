#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "Misc.h"
#include "Objects.h"
#include "GlobalVars.h"
#include "Scenes.h"
#include "Enemy.h"
#include <Windows.h>

#include <vector>
#include <utility>

class Player {

public:

	Point position;
	float height, width, speed, jumpForce, airSpeed, ogSpeed;
	//vec2 direction;

	float yDir, xDir;

	int standingIdx, walkingIdx, airIdx, coyoteFrames, curCoyoteFrame;

	int invincibilityFrames, curinvincibilityFrame;

	Sprite* sprite;

	std::vector<Sprite*> standingSprites;
	std::vector<Sprite*> walkingSprites;
	std::vector<Sprite*> airSprites;

	bool isP1, canJump, hasSprite;
	bool isMovingX, side;


public:

	Player(Point pos = Point(0, 0), float height = 50.0f, float width = 50.0f,
		bool hasSprite = false, float speed = 400.0f, float jumpForce = 14.0f,
		float airSpeed = 200.0f, bool isP1 = true);

	void fixCollisions(Point& nextPos, std::vector <Platform>& platforms, std::vector <Block*>& blocks, std::vector <Enemy*>& enemies);
	void draw(std::vector <std::vector <Pixel> >& matrix);
	Point getInputs();
	void mainCicle(std::vector <Platform>& platforms, std::vector <Block*>& blocks, std::vector <Enemy*>& enemies);
	void loadSprite(void(*playerSpriteFunc)(Sprite*, std::vector <Sprite*>&,
		std::vector <Sprite*>&, std::vector <Sprite*>&, bool));

};

#endif 
