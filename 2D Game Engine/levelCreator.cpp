#include "levelCreator.h"

LevelCreator::LevelCreator() {

	this->click = false;
	this->mouse1 = this->mouse2 = Point(0, 0);

}

void LevelCreator::creatorPlatform(int mouseX, int mouseY, std::vector <Platform>& platforms) {

	if (click) {

		mouse2.x = (float)mouseX;
		mouse2.y = (float)mouseY;

		Platform p = Platform(Point((mouse1.x + mouse2.x) / 2, (mouse1.y + mouse2.y) / 2.0f), fabs(mouse1.y - mouse2.y),
			fabs(mouse1.x - mouse2.x), 0, Pixel(rand() % 255, rand() % 255, rand() % 255));

		platforms.push_back(p);

		click = false;

		mouse1 = Point(0, 0);
		mouse2 = Point(0, 0);

	}
	else {

		mouse1.x = (float)mouseX;
		mouse1.y = (float)mouseY;

		click = true;

	}

}


void LevelCreator::creatorParticles(int mouseX, int mouseY, std::vector <Particles*>& particles) {
	particles.push_back(new Particles(Point(mouseX, mouseY), 1000, 4.0f, Pixel(rand() % 255, rand() % 255, rand() % 255)));
}

void LevelCreator::creatorBlock(int mouseX, int mouseY, std::vector <Block*>& blocks) {

	const int width = 40;
	const int height = 40;

	//if (globalvar.position.first < 0) mouseX = -mouseX;
	//if (globalvar.position.second < 0) mouseY = -mouseY;

	Point pos;

	int ogmouseX = mouseX;
	int ogmouseY = mouseY;

	mouseX = (int(mouseX + globalvar.position.first) / width) * width;
	mouseY = (int(mouseY + globalvar.position.second) / height) * height;

	if (mouseX > 0)
		pos.x = mouseX - globalvar.position.first + width / 2;
	else {
		mouseX = ogmouseX;
		mouseX = (int(mouseX + globalvar.position.first - width) / width) * width;
		pos.x = mouseX - globalvar.position.first + width / 2;
	}

	if (mouseY > 0)
		pos.y = mouseY - globalvar.position.second + height / 2;
	else {
		mouseY = ogmouseY;
		mouseY = (int(mouseY + globalvar.position.second - height) / height) * height;
		pos.y = mouseY - globalvar.position.second + height / 2;
	}

	if (globalvar.blockType == 9) {

		globalvar.mp[{mouseX + width / 2, mouseY + height / 2}] = false;

		for (int k = 0; k < blocks.size(); k++) {

			if (blocks[k]->position.x == pos.x && blocks[k]->position.y == pos.y) {

				delete blocks[k];
				blocks.erase(blocks.begin() + k);
				break;

			}

		}

		return;

	}

	if (globalvar.mp[{mouseX + width / 2, mouseY + height / 2}]) return;
	globalvar.mp[{mouseX + width / 2, mouseY + height / 2}] = true;

	switch (globalvar.blockType) {

	case 0:
		blocks.push_back(new Block(globalvar.BlockSprites[0], pos, height, width, 0.0f));
		blocks[blocks.size() - 1]->spriteIdx = 0;
		break;

	case 1:
		blocks.push_back(new Block(globalvar.BlockSprites[1], pos, height, width, 0.0f));

		blocks[blocks.size() - 1]->spriteIdx = 1;
		break;

	case 2:
		blocks.push_back(new Block(globalvar.BlockSprites[2], pos, height, width, 0.0f));
		blocks[blocks.size() - 1]->spriteIdx = 2;
		break;

	case 3:
		blocks.push_back(new Block(globalvar.BlockSprites[3], pos, height, width, 0.0f));
		blocks[blocks.size() - 1]->spriteIdx = 3;
		break;

	default:
		blocks.push_back(new Block(globalvar.BlockSprites[0], pos, height, width, 0.0f));
		blocks[blocks.size() - 1]->spriteIdx = 0;
		break;

	}

}
