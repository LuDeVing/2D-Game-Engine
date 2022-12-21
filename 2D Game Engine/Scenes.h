#ifndef SCENES_HEADER_H
#define SCENES_HEADER_H

#include <vector>
#include "Objects.h"
#include "Enemy.h"

void loadObjects1(std::vector <Block*>& blocks);

void loadEnemies1(std::vector <Enemy*>& enemies);

void loadPlayerSprites1(Sprite* sprite, std::vector <Sprite*>& standingSprites,
	std::vector <Sprite*>& walkingSprites, std::vector <Sprite*>& airSprites, bool isP1);

void loadEnemySprites1(Sprite* sprite, std::vector <Sprite*>& standingSprites,
	std::vector <Sprite*>& walkingSprites, std::vector <Sprite*>& airSprites);

#endif