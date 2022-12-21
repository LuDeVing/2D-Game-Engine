#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include "GlobalVars.h"
#include <utility>

class Button {

public:

	std::pair <int, int> position;
	int width, height;
	Sprite sprite;

	float luminescence;

	Button(std::pair <int, int> position, int width, int height,
		Sprite sprite, float luminescence = 1.0f);
	bool isColiding(int mouseX, int mouseY);

};

class GUI {

public:

	Sprite background;
	std::vector <Button> buttons;

	GUI(Sprite background);
	void draw(DisplayImage& displayImage);

};

#endif
