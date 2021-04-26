#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "Textbox.h"
using namespace std;

extern const int WIDTH;
extern const int HEIGHT;
class Textbox;
class Preloading {
public:
	Preloading();
	~Preloading();

	SDL_Texture* preloadBackground;
	Textbox* count;
	void center(); //center point of the screen, both vertically and horizontally centerize
	void update();
	void render();

private:
	uint32_t startTicks;
};