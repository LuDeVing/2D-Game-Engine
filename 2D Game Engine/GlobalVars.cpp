#include "GlobalVars.h"

Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;

}

DisplayImage::DisplayImage(){
	return;
}

DisplayImage::DisplayImage(unsigned int width, unsigned int height) {

	this->width = width;
	this->height = height;
	this->imageData = new unsigned char[width * height * 4];

}

void DisplayImage::Draw(int x, int y, Pixel color, unsigned int pixelSize) {

	int idx = (width * y + x) * 4;

	if (idx > this->width * this->height * 4 - 4)
		return;

	imageData[idx] = color.r;
	imageData[idx + 1] = color.g;
	imageData[idx + 2] = color.b;
	imageData[idx + 3] = color.a;

}

Sprite::Sprite() {

	this->width = 0;
	this->height = 0;

}

Sprite::Sprite(const char* filePath) {

	unsigned char* img = stbi_load(filePath, &width, &height, &channels, 0);

	if (img == NULL) {

		std::cout << "can't locate the file" << std::endl;
		std::cout << "filePath: " << filePath << std::endl;

		this->width = 0;
		this->height = 0;
		return;

	}

	image.resize(height, std::vector<Pixel>(width));

	int idx = 0;

	for (int k = 0; k < width * height * channels; k += channels) {

		image[idx / width][idx % width].r = img[k];
		image[idx / width][idx % width].g = img[k + 1];
		image[idx / width][idx % width].b = img[k + 2];

		image[idx / width][idx % width].a = (channels >= 4 ? img[k + 3] : 255);		

		idx++;

	}

	stbi_image_free(img);

}

Pixel Sprite::GetPixel(unsigned int x, unsigned int y) {

	if (x >= width || y >= height)
		return Pixel();

	return image[y][x];

}

GlobalVars::GlobalVars() {

	this->deltaTime = 1.0f;
	this->GravityStrengh = 0.5f;
	this->AirFriction = 0.925f;

	this->position = { 0, 0 };

	this->blockType = 0;

}
