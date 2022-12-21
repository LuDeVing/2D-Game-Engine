#ifndef CREATOR_CLASS_H
#define CREATOR_CLASS_H

	#include "Misc.h"
#include "Objects.h"
#include "GlobalVars.h"
#include "ParticleSystem.h"

#include <vector>

class LevelCreator {

public:

	bool click;
	Point mouse1, mouse2;

	LevelCreator();

	void creatorBlock(int mouseX, int mouseY, std::vector <Block*>& blocks);
	void creatorPlatform(int mouseX, int mouseY, std::vector <Platform>& platforms);
	void creatorParticles(int mouseX, int mouseY, std::vector <Particles*>& particles);

};

#endif