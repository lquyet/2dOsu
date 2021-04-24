#pragma once
#include "Texture.h"

class StartScreen {
public:
	StartScreen();
	~StartScreen();

	void update();
	void render();
private:
	SDL_Texture* startScreenBackground;
	SDL_Texture* button[4];
};