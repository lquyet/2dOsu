#pragma once
#include "Texture.h"
#include "Button.h"

class Button; // forward declaration 

enum buttonDetail {
	START = 0,
	OPTION = 1,
	EXIT = 2
};

class StartScreen {
public:
	StartScreen();
	~StartScreen();
	void update();
	void render();
	Button* button[3];
private:
	SDL_Texture* startScreenBackground;

};