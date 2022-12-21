#include "Misc.h"

//2D Vector

vec2::vec2(float xp, float yp) {
	this->x = xp;
	this->y = yp;
}

void vec2::normalize() {

	float length = sqrtf((this->x + this->y) * (this->x + this->y));

	this->x /= length;
	this->y /= length;

}

void vec2::add(vec2& addVector) {
	this->x += addVector.x * globalvar.deltaTime;
	this->y += addVector.y * globalvar.deltaTime;
}

//POINT

Point::Point(float xp, float yp) {
	this->x = xp;
	this->y = yp;
}

//Collision detection

bool point_in_square(Point& p1, Point& p2, float minX, float maxX, float minY, float maxY) {

	bool ans1 = (p1.x >= minX && p1.x <= maxX && p1.y >= minY && p1.y <= maxY);
	bool ans2 = (p2.x >= minX && p2.x <= maxX && p2.y >= minY && p2.y <= maxY);

	bool ans3 = (p2.x <= minX && p1.x >= maxX && p1.y >= minY && p1.y <= maxY);
	bool ans4 = (p2.y <= minY && p1.y >= maxY && p1.x >= minX && p1.x <= maxX);

	//	std::cout << ans3 << ' ' << ans4 << '\n';

	return (ans1 || ans2 || ans3 || ans4);
}

bool Collision(Point pos1, float hight1, float width1, Point pos2, float hight2, float width2) {

	Point upp_right1 = { pos1.x + width1 / 2, pos1.y + hight1 / 2 };
	Point down_left1 = { pos1.x - width1 / 2, pos1.y - hight1 / 2 };
	Point down_right1 = { pos1.x + width1 / 2, pos1.y - hight1 / 2 };
	Point upp_left1 = { pos1.x - width1 / 2, pos1.y + hight1 / 2 };

	Point upp_right2 = { pos2.x + width2 / 2, pos2.y + hight2 / 2 };
	Point down_left2 = { pos2.x - width2 / 2, pos2.y - hight2 / 2 };
	Point down_right2 = { pos2.x + width2 / 2, pos2.y - hight2 / 2 };
	Point upp_left2 = { pos2.x - width2 / 2, pos2.y + hight2 / 2 };

	bool ans = false;

	ans |= point_in_square(upp_right1, upp_left1, down_left2.x, upp_right2.x, down_left2.y, upp_right2.y);
	ans |= point_in_square(down_right1, down_left1, down_left2.x, upp_right2.x, down_left2.y, upp_right2.y);
	ans |= point_in_square(upp_right1, down_right1, down_left2.x, upp_right2.x, down_left2.y, upp_right2.y);
	ans |= point_in_square(upp_left1, down_left1, down_left2.x, upp_right2.x, down_left2.y, upp_right2.y);

	ans |= point_in_square(upp_right2, upp_left2, down_left1.x, upp_right1.x, down_left1.y, upp_right1.y);
	ans |= point_in_square(down_right2, down_left2, down_left1.x, upp_right1.x, down_left1.y, upp_right1.y);
	ans |= point_in_square(upp_right2, down_right2, down_left1.x, upp_right1.x, down_left1.y, upp_right1.y);
	ans |= point_in_square(upp_left2, down_left2, down_left1.x, upp_right1.x, down_left1.y, upp_right1.y);

	return ans;
}

bool isOnScreen(Point& pos, int width, int height) {

	bool xAns = (pos.x + width / 2 >= 0 && pos.x - width / 2 < globalvar.screenWidth);
	bool yAns = (pos.y + height / 2 >= 0 && pos.y - height / 2 < globalvar.screenHeight);

	return (xAns && yAns);

}

// physics

void getGravity(float& yDir) {
	yDir += globalvar.GravityStrengh;
	yDir = min(yDir, 15.0f);
}

void getAirFriction(float& xDir) {

	xDir *= globalvar.AirFriction;

	if (fabs(xDir) < 0.001f)
		xDir = 0;

}
