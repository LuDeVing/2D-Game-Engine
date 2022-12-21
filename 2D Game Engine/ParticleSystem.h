#ifndef PARTICLE_SYSTEM_HEADER_H
#define PARTICLE_SYSTEM_HEADER_H

#include "Misc.h"

#include <vector>
#include <utility>

struct Particle {

	Point position;
	float xDir, yDir;
	int lifeFrames;

	Particle(Point position = Point(0, 0), float xDir = 0, float yDir = 0, int lifeFrames = 0);

};

class Particles {

	int rangeXbegin, rangeXend, lifeFrames, width, height, rangeYbegin, rangeYend;
	float ParticleSpeedDeclineX, ParticleSpeedAccendY, speedMultiplier;
	Pixel color;

	unsigned int currentFrame, nextFrame, maxTimeDifference, activeTime;

public:

	std::vector <Particle> particles;

	Point startingPos;
	bool hasEnded;

	Particles(
		Point startingPos = Point(), unsigned int activeTime = 1000, float speedMultiplier = 1.0f,
		Pixel color = Pixel(255, 255, 255), int rangeYbegin = -2, int rangeYend = 0,
		int rangeXbegin = -15, int rangeXend = 15, unsigned int maxTimeDifference = 5, unsigned int lifeFrames = 1000,
		int height = 2, int width = 2, float ParticleSpeedDeclineX = 0.1f, float ParticleSpeedAccendY = 7.5f
	);

	void mainCicle(std::vector <std::vector <Pixel> >& matrix);
	void draw(std::vector <std::vector <Pixel> >& matrix, int idx);

};

#endif
