#pragma once
#include "Texture.h"

class Button {
public:
	Button(std::string pathToImage, const int &x, const int &y);
	Button();
	~Button();
	void focus(bool focus);
	void update();
	void render();
	SDL_Rect dst;
	SDL_Color focusColor;
	bool bFocus;
private:
	int bWidth;
	int bHeight;
	SDL_Texture* button;

};