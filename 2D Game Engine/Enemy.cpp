#include "Enemy.h"

Enemy::Enemy(Point pos, float walkableDistance, float height, float width, bool hasSprite, float speed, float airSpeed) {

	this->position = pos;
	this->height = height;
	this->width = width;
	this->speed = speed;
	this->airSpeed = airSpeed;
	this->ogSpeed = speed;
	this->walkableDistance = walkableDistance;

	this->yDir = 0.0f;

	this->hasSprite = hasSprite;
	this->sprite = new Sprite();

	this->side = true;
	this->isMovingX = false;
	this->isActive = false;

	this->walkedDistance = 0;
	this->standingIdx = 0;
	this->walkingIdx = 0;
	this->airIdx = 0;

}

void Enemy::draw(std::vector <std::vector <Pixel> >& matrix) {

	Point startPoint = { position.x - width / 2, position.y + height / 2 };
	Point finalPoint = { position.x + width / 2, position.y - height / 2 };

	float xB = 0.0f, yB = 0.0f, dx, dy;

	dx = sprite->width / ((float)width + 1);
	dy = sprite->height / ((float)height + 1);

	for (int y = (int)finalPoint.y; y <= (int)startPoint.y; y++) {

		xB = 0.0f;

		if (y < 0 || y >= matrix.size()) {
			yB += dy;
			continue;
		}

		if (side) {

			for (int x = (int)startPoint.x; x <= (int)finalPoint.x; x++) {

				if (x < 0 || x >= matrix[y].size()) {
					xB += dx;
					continue;
				}

				if (sprite->GetPixel(floorf(xB), floorf(yB)).a != 0)
					matrix[y][x] = sprite->GetPixel(floorf(xB), floorf(yB));

				xB += dx;

			}

		}
		else {

			for (int x = (int)finalPoint.x; x >= (int)startPoint.x; x--) {

				if (x < 0 || x >= matrix[y].size()) {
					xB += dx;
					continue;
				}

				if (sprite->GetPixel(floorf(xB), floorf(yB)).a != 0)
					matrix[y][x] = sprite->GetPixel(floorf(xB), floorf(yB));

				xB += dx;

			}

		}

		yB += dy;

	}

}

void Enemy::fixCollisions(Point& nextPos, std::vector <Platform>& platforms, std::vector <Block*>& blocks) {

	bool isGrounded = false;

	for (const auto& platform : platforms) {

		bool col1 = Collision(Point(nextPos.x, position.y), height, width,
			platform.position, platform.height, platform.width);

		bool col2 = Collision(Point(position.x, nextPos.y), height, width,
			platform.position, platform.height, platform.width);

		float heightDiff = min(
			abs((platform.position.y - platform.height / 2.0f) - (position.y + height / 2.0f)),
			abs((platform.position.y + platform.height / 2.0f) - (position.y - height / 2.0f))
		);

		float platformMaxX = platform.position.x + (platform.width / 2 + width / 2) + 1;
		float platformMinX = platform.position.x - (platform.width / 2 + width / 2) - 1;

		float platformMaxY = platform.position.y - (platform.height / 2 + height / 2) - 1;
		float platformMinY = platform.position.y + (platform.height / 2 + height / 2) + 1;

		std::vector <std::pair <bool, Point> > v;

		if (col1) {

			if (nextPos.x > position.x) {
				v.push_back({ false, Point(min(nextPos.x, platformMinX), nextPos.y) });
			}
			else if (nextPos.x < position.x) {
				v.push_back({ false, Point(max(nextPos.x, platformMaxX), nextPos.y) });
			}

		}

		if (col2) {

			if (nextPos.y >= position.y) {
				v.push_back({ true, Point(nextPos.x, floorf(min(nextPos.y, platformMaxY))) });
			}
			else {
				v.push_back({ true, Point(nextPos.x, max(nextPos.y, platformMinY)) });
			}

		}

		bool usedY = false;

		if (v.size() == 1) {
			nextPos = v[0].second;
			usedY = v[0].first;
		}
		else if (v.size() == 2) {

			if (v[0].first > v[1].first)
				std::swap(v[0], v[1]);

			bool col1 = Collision(Point(v[0].second.x, position.y), height, width,
				platform.position, platform.height, platform.width);

			bool col2 = Collision(Point(position.x, v[0].second.y), height, width,
				platform.position, platform.height, platform.width);

			if (!col1 && !col2) {

				float d1 = position.x - v[0].second.x;
				d1 *= d1;

				float d2 = position.y - v[1].second.y;
				d2 *= d2;

				if (d1 < d2) nextPos = v[0].second;
				else  nextPos = v[1].second;

			}
			else if (!col1) {
				nextPos = v[0].second;
			}
			else if (!col2) {
				nextPos = v[1].second;
				usedY = true;
			}
			else {

				nextPos.x = v[0].second.x;
				nextPos.y = v[1].second.y;
				usedY = true;

			}

		}

		if (usedY) {

			if (yDir >= 0) {


				yDir = min(yDir, 0.0f);
				speed = ogSpeed;

				isGrounded = true;

				nextPos.y = floorf(nextPos.y);

			}
			else {

				yDir = 0;
				nextPos.y = ceilf(nextPos.y);

			}

		}

	}

	for (const auto& block : blocks) {

		bool col1 = Collision(Point(nextPos.x, position.y), height, width,
			block->position, block->height, block->width);

		bool col2 = Collision(Point(position.x, nextPos.y), height, width,
			block->position, block->height, block->width);

		float heightDiff = min(
			abs((block->position.y - block->height / 2.0f) - (position.y + height / 2.0f)),
			abs((block->position.y + block->height / 2.0f) - (position.y - height / 2.0f))
		);

		float platformMaxX = block->position.x + (block->width / 2 + width / 2) + 1;
		float platformMinX = block->position.x - (block->width / 2 + width / 2) - 1;

		float platformMaxY = block->position.y - (block->height / 2 + height / 2) - 1;
		float platformMinY = block->position.y + (block->height / 2 + height / 2) + 1;

		std::vector <std::pair <bool, Point> > v;

		if (col1) {

			if (nextPos.x > position.x) {
				v.push_back({ false, Point(min(nextPos.x, platformMinX), nextPos.y) });
			}
			else if (nextPos.x < position.x) {
				v.push_back({ false, Point(max(nextPos.x, platformMaxX), nextPos.y) });
			}

		}

		if (col2) {

			if (nextPos.y >= position.y) {
				v.push_back({ true, Point(nextPos.x, floorf(min(nextPos.y, platformMaxY))) });
			}
			else {
				v.push_back({ true, Point(nextPos.x, max(nextPos.y, platformMinY)) });
			}

		}

		bool usedY = false;

		if (v.size() == 1) {
			nextPos = v[0].second;
			usedY = v[0].first;
		}
		else if (v.size() == 2) {

			if (v[0].first > v[1].first)
				std::swap(v[0], v[1]);

			bool col1 = Collision(Point(v[0].second.x, position.y), height, width,
				block->position, block->height, block->width);

			bool col2 = Collision(Point(position.x, v[0].second.y), height, width,
				block->position, block->height, block->width);

			if (!col1 && !col2) {

				float d1 = position.x - v[0].second.x;
				d1 *= d1;

				float d2 = position.y - v[1].second.y;
				d2 *= d2;

				if (d1 < d2) nextPos = v[0].second;
				else  nextPos = v[1].second;

			}
			else if (!col1) {
				nextPos = v[0].second;
			}
			else if (!col2) {
				nextPos = v[1].second;
				usedY = true;
			}
			else {

				nextPos.x = v[0].second.x;
				nextPos.y = v[1].second.y;
				usedY = true;

			}

		}

		if (usedY) {

			if (yDir >= 0) {


				yDir = min(yDir, 0.0f);
				speed = ogSpeed;

				isGrounded = true;

				nextPos.y = floorf(nextPos.y);

			}
			else {

				yDir = 0;
				nextPos.y = ceilf(nextPos.y);

			}

		}

	}
	if (yDir >= 0) nextPos.y = floorf(nextPos.y);

}

void Enemy::loadSprite(void(*enemySpriteFunc)(Sprite*, std::vector <Sprite*>&,
	std::vector <Sprite*>&, std::vector <Sprite*>&)) {

	enemySpriteFunc(sprite, standingSprites, walkingSprites, airSprites);

}

Point Enemy::getMovement() {

	Point nextPos = position;

	if (side) {
		nextPos.x += speed * globalvar.deltaTime;
		walkedDistance += speed * globalvar.deltaTime;
		isMovingX = true;
	}
	else {
		nextPos.x -= speed * globalvar.deltaTime;
		walkedDistance -= speed * globalvar.deltaTime;
		isMovingX = true;
	}

	if ((side && walkedDistance >= walkableDistance / 2.0f)
		|| (!side && walkedDistance <= -walkableDistance / 2.0f))
		side = !side;


	nextPos.y += yDir;

	return nextPos;

}

void Enemy::mainCicle(std::vector <Platform>& platforms, std::vector <Block*>& blocks) {

	if (!isActive) {

		if (isOnScreen(position, width, height))
			isActive = true;
		else return;

	}

	isMovingX = false;

	Point nextPos = this->getMovement();

	fixCollisions(nextPos, platforms, blocks);

	bool isInAir = (position.y != nextPos.y);

	position = nextPos;

	if (isInAir) {
		if (airSprites.size() != 0)
			sprite = airSprites[(++airIdx) % airSprites.size()];
	}
	else if (isMovingX) {
		if (walkingSprites.size() != 0)
			sprite = walkingSprites[(++walkingIdx) % walkingSprites.size()];
	}
	else {
		if (standingSprites.size() != 0)
			sprite = standingSprites[(++standingIdx) % standingSprites.size()];
	}

	getGravity(this->yDir);

}