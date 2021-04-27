#pragma once
#include "Button.h"

class Textbox {
public:
	Textbox(std::string message, TTF_Font* font, SDL_Color color, const int &x, const int &y);
	~Textbox();
	void render();
	void update(std::string msg, TTF_Font* font, SDL_Color color);
	void scoreEffect(TTF_Font* fontList[10], std::string msg, SDL_Color color);
	void center(const int& x);
	void center(const int& x, const int& y);
	std::string message;
	//SDL_Color color;
	void moveX(int distance);
	void moveY(int distance);
	SDL_Rect dst;
private:
	SDL_Texture* text;
	//TTF_Font* tFont;
};