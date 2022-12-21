#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <vector>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include "GlobalVars.h"
#include "Misc.h"
#include "Player.h"
#include "Objects.h"
#include "Camera.h"
#include "levelCreator.h"
#include "ParticleSystem.h"
#include "Scenes.h"
#include "Enemy.h"
#include "GUI.h"

unsigned int screenWidth = 640;
unsigned int screenHeight = 360;

int frameTime = 0, lastTime = 0, curTime = 0;

void render(void);
void timer_callback(int);

Camera camera;
Point position;
Player chichikia;
LevelCreator levelCreator;
Sprite backGround;

DisplayImage displayImage;

std::vector <Block*> blocks;
std::vector <Enemy*> enemies;
std::vector <Platform> platforms;
std::vector <Particles*> particles;
std::vector <std::vector <Pixel> > matrix;

GLuint textureID;
GUI* currentGui;

const long long int maxLClickDifferenceFrames = 15;
long long int lastLclick = -10000;
long long int curLClick = 0;

int framesBeforeCreator = 40;

unsigned int upscale = 2;
bool doFullScreen = true;
bool activeGUI = true;

int GetMouseX() {

	POINT mousePos;
	GetCursorPos(&mousePos);

	return (mousePos.x - glutGet(GLUT_WINDOW_X)) / upscale;

}

int GetMouseY() {

	POINT mousePos;
	GetCursorPos(&mousePos);

	return (mousePos.y - glutGet(GLUT_WINDOW_Y)) / upscale;

}

void setFrameRate() {

	int framerate = min(62, round(1000.0 / frameTime));

	globalvar.deltaTime = 1.0f / min(62.0f, framerate);

	char windowName[] = "2D Game Engine     fps";
	char fps[3];
	if (framerate / 100 > 0) {
		fps[0] = framerate / 100 + '0';
	}
	else fps[0] = ' ';
	if (framerate / 10 % 10 != 0 || framerate / 100 != 0) {
		fps[1] = (framerate / 10 % 10) + '0';
	}
	else fps[1] = ' ';
	fps[2] = (framerate % 10) + '0';
	windowName[16] = fps[0];
	windowName[17] = fps[1];
	windowName[18] = fps[2];

	glutSetWindowTitle(windowName);

}

void GetDesktopResolution(int& horizontal, int& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void loadScene1() {

	backGround = Sprite("images/backGrounds/mountainsBackground.png");
	chichikia = Player(Point(float(screenWidth / 2), float(screenHeight + 10)), 78, 27, true);

	void(*playerSpriteFunc)(Sprite*, std::vector <Sprite*>&,
		std::vector <Sprite*>&, std::vector <Sprite*>&, bool) = loadPlayerSprites1;

	chichikia.loadSprite(playerSpriteFunc);

	globalvar.BlockSprites.push_back(new Sprite("images/Platforms/mainBlock.png"));
	globalvar.BlockSprites.push_back(new Sprite("images/Platforms/brickBlock.png"));
	globalvar.BlockSprites.push_back(new Sprite("images/Platforms/strongBlock.png"));
	globalvar.BlockSprites.push_back(new Sprite("images/Platforms/questionBlock.png"));

	loadObjects1(blocks);

}

void getCreatorInputs() {
	
	if (framesBeforeCreator > 0) {
		framesBeforeCreator--;
		return;
	}

	curLClick++;

	if (GetAsyncKeyState(0x30)) {
		globalvar.blockType = 0;
	}

	if (GetAsyncKeyState(0x31)) {
		globalvar.blockType = 1;
	}

	if (GetAsyncKeyState(0x32)) {
		globalvar.blockType = 2;
	}

	if (GetAsyncKeyState(0x32)) {
		globalvar.blockType = 3;
	}

	if (GetAsyncKeyState(0x39)) {
		globalvar.blockType = 9;
	}

	if ((GetKeyState(VK_LBUTTON)) & 0x8000) {
		levelCreator.creatorBlock(GetMouseX(), GetMouseY(), blocks);
	}

	if (GetAsyncKeyState(VK_RBUTTON) && abs(curLClick - lastLclick) >= maxLClickDifferenceFrames) {

		//enemies.push_back(new Enemy(Point(GetMouseX(), GetMouseY())));
		//enemies[enemies.size() - 1]->loadSprite(loadEnemySprites1);

		levelCreator.creatorParticles(GetMouseX(), GetMouseY(), particles);

		//lastLclick = curLClick;


	}

	if (GetAsyncKeyState(0x39)) {

		system("CLS");

		for (int k = 0; k < blocks.size(); k++) {

			Point pos;

			pos.x = globalvar.position.first + blocks[k]->position.x;
			pos.y = globalvar.position.second + blocks[k]->position.y;

			std::cout << "blocks.push_back(new Block(";
			std::cout << "globalvar.BlockSprites[" << blocks[k]->spriteIdx << "],  ";
			std::cout << "Point(" << pos.x << ", " << pos.y << "), 40, 40));\n";
			std::cout << "blocks[blocks.size() - 1]->spriteIdx = " << blocks[k]->spriteIdx << ";\n";
			std::cout << "globalvar.mp[{" << pos.x << ", " << pos.y << "}] = true;\n";

		}

		std::cout << "\n\n\n\n\n\n\n\n\n\n\n";

		for (int k = 0; k < enemies.size(); k++) {

			Point pos;

			pos.x = globalvar.position.first + enemies[k]->position.x;
			pos.y = globalvar.position.second + enemies[k]->position.y;

			std::cout << "enemies.push_back(new Enemy(Point(" << pos.x << ", " << pos.y << ")));\n";
			std::cout << "enemies[enemies.size() - 1]->loadSprite(loadEnemySprites1);\n";

		}

	}
	
}

void moveCamera() {

	camera.mainCicle(chichikia, platforms, blocks, particles, enemies, screenWidth, screenHeight);
	//camera.adjustPosition(levelCreator.mouse1, ScreenWidth(), ScreenHeight());

}

void particlesCicle() {

	for (int k = 0; k < particles.size(); k++) {

		particles[k]->mainCicle(matrix);
		camera.adjustPosition(particles[k]->startingPos, screenWidth, screenHeight);

		if (particles[k]->hasEnded && particles[k]->particles.size() == 0) {

			delete particles[k];
			particles.erase(particles.begin() + k);
			k--;

		}

	}

}

void createOpenGLTexture() {
	
	glGenTextures(1, &textureID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

}

void DrawAll() {

	float xB = 0.0f, yB = 0.0f, dx, dy;

	dx = backGround.width / (float)screenWidth;
	dy = backGround.height / (float)screenHeight;


	for (int y = 0; y < matrix.size(); y++) {

		xB = 0.0f;

		for (int x = 0; x < matrix[y].size(); x++) {

			if (matrix[y][x].a != 255)
				displayImage.Draw(x, screenHeight - y - 1, backGround.GetPixel(floorf(xB), floorf(yB)));
			
			displayImage.Draw(x, screenHeight - y - 1, matrix[y][x]);

			matrix[y][x] = backGround.GetPixel(floorf(xB), floorf(yB));

			xB += dx;

		}

		yB += dy;
	}

}

void render() {

	glClear(GL_COLOR_BUFFER_BIT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, displayImage.width, displayImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, displayImage.imageData);
	
	GLuint fboId = 0;
	glGenFramebuffers(1, &fboId);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fboId);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, textureID, 0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, screenWidth, screenHeight, 0, 0,
		screenWidth * upscale, screenHeight * upscale, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glFlush();

}

void OnGuiCreate() {

	currentGui = new GUI(Sprite("images/GUI/GUIbg.png"));

	currentGui->buttons.push_back(Button(
		{ screenWidth / 2, screenHeight / 2 - screenHeight / 20},
		screenWidth / 4,
		screenHeight / 10,
		Sprite("images/GUI/playButton.png")
	));

	currentGui->buttons.push_back(Button(
		{ screenWidth / 2, screenHeight / 2 + screenHeight / 10 },
		screenWidth / 4,
		screenHeight / 10,
		Sprite("images/GUI/quitButton.png")
	));

}

void OnGuiUpdate() {

	if (currentGui->buttons[0].isColiding(GetMouseX(), GetMouseY())) {
	
		currentGui->buttons[0].luminescence = 0.5f;

		if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
			framesBeforeCreator = 40;
			activeGUI = false;
			PlaySound(TEXT("sounds/misc/click.wav"), NULL, SND_ASYNC);
		}
		

	}
	else currentGui->buttons[0].luminescence = 1.0f;

	if (currentGui->buttons[1].isColiding(GetMouseX(), GetMouseY())) {

		currentGui->buttons[1].luminescence = 0.5f;

		if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
			PlaySound(TEXT("sounds/misc/quitClick.wav"), NULL, SND_ASYNC);
			Sleep(105);
			exit(0);
		}

	}
	else currentGui->buttons[1].luminescence = 1.0f;

	currentGui->draw(displayImage);

	render();

}

void OnUserCreate() {

	globalvar.screenHeight = screenHeight;
	globalvar.screenWidth = screenWidth;

	globalvar.fullScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	globalvar.fullScreenWidth = GetSystemMetrics(SM_CXSCREEN);

	loadScene1();
	loadEnemies1(enemies);

	createOpenGLTexture();

	camera = Camera(0.05f);

	matrix.resize(screenHeight, std::vector<Pixel>(screenWidth, Pixel(0, 0, 150)));
	displayImage = DisplayImage(screenWidth, screenHeight);
	//displayImage = DisplayImage(globalvar.fullScreenWidth, globalvar.fullScreenHeight);

}

void OnUserUpdate() {

	auto start = std::chrono::high_resolution_clock::now();

	//screenWidth = glutGet(GLUT_WINDOW_WIDTH);
	//screenHeight = glutGet(GLUT_WINDOW_HEIGHT);

	globalvar.screenWidth = screenWidth;
	globalvar.screenHeight = screenHeight;

	globalvar.fullScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	globalvar.fullScreenWidth = GetSystemMetrics(SM_CXSCREEN);

	moveCamera();

	camera.adjustPosition(globalvar.position, screenWidth, screenHeight);
	getCreatorInputs();

	chichikia.mainCicle(platforms, blocks, enemies);
	particlesCicle();

	for (int k = 0; k < platforms.size(); k++) {
		if (isOnScreen(platforms[k].position, platforms[k].width, platforms[k].height))
			platforms[k].draw(matrix);
	}

	for (int k = 0; k < blocks.size(); k++) {
		if (isOnScreen(blocks[k]->position, blocks[k]->width, blocks[k]->height))
			blocks[k]->draw(matrix);
	}

	for (int k = 0; k < enemies.size(); k++) {

		enemies[k]->mainCicle(platforms, blocks);

		if (isOnScreen(enemies[k]->position, enemies[k]->width, enemies[k]->height))
			enemies[k]->draw(matrix);

	}

	chichikia.draw(matrix);

	DrawAll();
	render();

	//Sprite image = Sprite("images/image.png");
	//std::cout << image.width << ' ' << image.height << '\n';

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	
	frameTime = duration.count();
	
	setFrameRate();

	if (GetAsyncKeyState(VK_ESCAPE))
		activeGUI = true;

}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth * upscale, screenHeight * upscale);
	glutCreateWindow("2D game engine");

	if(doFullScreen){

		int hor, vert;
		GetDesktopResolution(hor, vert);

		upscale = min(hor / screenWidth, vert / screenHeight);
		glutFullScreen();

	}

	glewInit();

	OnUserCreate();
	OnGuiCreate();

	glutTimerFunc(5, timer_callback, 0);
	//glutDisplayFunc(render);

	glutMainLoop();	

}

void timer_callback(int) {

	if (activeGUI) OnGuiUpdate();
	else OnUserUpdate();

	glutTimerFunc(max(0, 16 - frameTime), timer_callback, 0);

} 
