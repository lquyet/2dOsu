#pragma once
#include "Button.h"

class Textbox {
public:
	Textbox(std::string message, TTF_Font* font, SDL_Color color, const int &x, const int &y);
	~Textbox();
	void render();
	void update(std::string msg, TTF_Font* font, SDL_Color color);
	void scoreEffect();
private:
	SDL_Rect dst;
	SDL_Texture* text;
};