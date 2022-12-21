#include "ParticleSystem.h"

Particles::Particles(
	Point startingPos, unsigned int activeTime, float speedMultiplier, Pixel color, int rangeYbegin, int rangeYend, int rangeXbegin, int rangeXend,
	unsigned int maxTimeDifference, unsigned int lifeFrames, int height, int width, float ParticleSpeedDeclineX, float ParticleSpeedAccendY) {

	this->startingPos = startingPos;
	this->lifeFrames = lifeFrames;
	this->ParticleSpeedDeclineX = ParticleSpeedDeclineX;
	this->maxTimeDifference = maxTimeDifference;
	this->activeTime = activeTime;
	this->ParticleSpeedAccendY = ParticleSpeedAccendY;
	this->speedMultiplier = speedMultiplier;

	this->rangeXbegin = rangeXbegin;
	this->rangeXend = rangeXend;
	this->rangeYbegin = rangeYbegin;
	this->rangeYend = rangeYend;

	this->hasEnded = false;
	this->currentFrame = 0;
	this->nextFrame = 0;

	this->color = color;

	this->width = width;
	this->height = height;

}

Particle::Particle(Point position, float xDir, float yDir, int lifeFrames) {

	this->position = position;
	this->xDir = xDir;
	this->yDir = yDir;
	this->lifeFrames = lifeFrames;

}

void Particles::draw(std::vector <std::vector <Pixel> >& matrix, int idx) {

	Point startPoint = { particles[idx].position.x - width / 2, particles[idx].position.y + height / 2 };
	Point finalPoint = { particles[idx].position.x + width / 2, particles[idx].position.y - height / 2 };

	for (int y = (int)startPoint.y; y >= (int)finalPoint.y; y--) {
		for (int x = (int)startPoint.x; x <= (int)finalPoint.x; x++) {

			if (y < 0 || y >= matrix.size()) continue;
			if (x < 0 || x >= matrix[y].size()) continue;

			matrix[y][x] = color;

		}
	}

}

void Particles::mainCicle(std::vector <std::vector <Pixel> >& matrix) {

	//camera.adjustPosition(startingPos);

	currentFrame++;

	if (currentFrame >= nextFrame && !hasEnded) {

		nextFrame += int(rand() % maxTimeDifference + 1);
		particles.push_back(Particle(startingPos, rand() % (rangeXend - rangeXbegin) + rangeXbegin, rand() % (rangeYend - rangeYbegin) + rangeYbegin, lifeFrames));

	}

	for (int k = 0; k < particles.size(); k++) {

		if (particles[k].position.y > globalvar.screenHeight) {
			particles.erase(particles.begin() + k);
			continue;
		}

		getGravity(particles[k].yDir);

		particles[k].position.y += particles[k].yDir * speedMultiplier * globalvar.deltaTime * ParticleSpeedAccendY;
		particles[k].position.x += particles[k].xDir * speedMultiplier * globalvar.deltaTime * ParticleSpeedDeclineX;

		particles[k].lifeFrames--;
		draw(matrix, k);

		if (particles[k].lifeFrames <= 0)
			particles.erase(particles.begin() + k);

	}

	if (currentFrame >= activeTime)
		hasEnded = true;

}
