#include "GUI.h"

Button::Button(std::pair <int, int> position, int width, int height, Sprite sprite, float luminescence) {

	this->luminescence = luminescence;
	this->position = position;
	this->sprite = sprite;
	this->height = height;
	this->width = width;

}

bool Button::isColiding(int mouseX, int mouseY) {

	return (mouseX >= this->position.first - this->width / 2
		 && mouseX <= this->position.first + this->width / 2
		 && mouseY >= this->position.second - this->height / 2
		 && mouseY <= this->position.second + this->height / 2);

}

GUI::GUI(Sprite background) {
	this->background = background;
}

void GUI::draw(DisplayImage& displayImage) {

	float xB = 0.0f, yB = 0.0f, dx, dy;

	int screenWidth = globalvar.screenWidth;
	int screenHeight = globalvar.screenHeight;

	dx = background.width / (float)screenWidth;
	dy = background.height / (float)screenHeight;

	for (int y = 0; y < screenHeight; y++) {

		xB = 0.0f;

		for (int x = 0; x < screenWidth; x++) {
			
			displayImage.Draw(x, screenHeight - y - 1,
				background.GetPixel(floor(xB), floor(yB)));
			
			xB += dx;
		
		}

		yB += dy;
	}

	for (int k = 0; k < buttons.size(); k++) {

		int startX, endX;
		int startY, endY;

		startX = buttons[k].position.first - buttons[k].width / 2;
		endX = buttons[k].position.first + buttons[k].width / 2;

		startY = buttons[k].position.second - buttons[k].height / 2;
		endY = buttons[k].position.second + buttons[k].height / 2;

		xB = 0.0f, yB = 0.0f;

		dx = buttons[k].sprite.width / (float)buttons[k].width;
		dy = buttons[k].sprite.height / (float)buttons[k].height;

		for (int y = startY; y <= endY; y++) {

			xB = 0.0f;

			for (int x = startX; x <= endX; x++) {
				
				Pixel cur = buttons[k].sprite.GetPixel(floor(xB), floor(yB));
	
				cur.r *= buttons[k].luminescence;
				cur.g *= buttons[k].luminescence;
				cur.b *= buttons[k].luminescence;

				displayImage.Draw(x, screenHeight - y - 1, cur);

				xB += dx;

			}

			yB += dy;

		}

	}

}

