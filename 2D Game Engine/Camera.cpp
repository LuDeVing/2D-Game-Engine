#include "Camera.h"

Camera::Camera(float followSpeed) {

	this->followSpeed = followSpeed;
	this->difference = Point(0, 0);
	this->nextPosition = Point(0, 0);

}

void Camera::follow(Point positionP, float dy) {

	Point diff;

	diff.x = (positionP.x - globalvar.screenWidth / 2) * followSpeed;
	diff.y = (positionP.y - globalvar.screenHeight / 2) * followSpeed;

	difference = diff;

}

void Camera::adjustPosition(Point& pos,
	float screenWidth, float screenheight) {

	pos.x -= floorf(difference.x);
	pos.y -= floorf(difference.y);

	//	pos.x += screenWidth / 2;
	//	pos.y += screenheight / 2;

}

void Camera::adjustPosition(std::pair <float, float>& pos,
	float screenWidth, float screenheight) {

	pos.first += floorf(difference.x);
	pos.second += floorf(difference.y);

	//pos.first += screenWidth / 2;
	//pos.second += screenheight / 2;


}

void Camera::mainCicle(Player& p1, std::vector<Platform>& platforms, std::vector<Block*>& blocks,
	std::vector<Particles*>& particles, std::vector <Enemy*>& enemies, float screenWidth, float screenheight) {

	follow(p1.position, p1.height * 2);
	adjustPosition(p1.position, screenWidth, screenheight);

	for (int k = 0; k < platforms.size(); k++)
		adjustPosition(platforms[k].position, screenWidth, screenheight);

	for (int k = 0; k < blocks.size(); k++)
		adjustPosition(blocks[k]->position, screenWidth, screenheight);

	for (int k = 0; k < enemies.size(); k++)
		adjustPosition(enemies[k]->position, screenWidth, screenheight);

	for (int k = 0; k < particles.size(); k++)
		for (int j = 0; j < particles[k]->particles.size(); j++)
			adjustPosition(particles[k]->particles[j].position, screenWidth, screenheight);

}