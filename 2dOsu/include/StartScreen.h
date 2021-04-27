#pragma once
#include "Texture.h"
#include "Button.h"
#include "Textbox.h"
class Button; // forward declaration 
class Textbox;

enum StartScreenButtonDetail {
	START = 0,
	OPTION = 1,
	EXIT = 2, 
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

enum EndScreenButtonDetail {
	RESTART = 0,
	QUIT  = 1
};

class EndScreen {
public:
	EndScreen(int score);
	~EndScreen();
	void update();
	void render();
	Button* button[2];
private:
	SDL_Texture* endScreenBackground;
	Textbox* tScore;
	Textbox* failMsg;
};