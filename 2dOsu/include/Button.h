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
private:
	int bWidth;
	int bHeight;
	SDL_Texture* button;
	bool bFocus;
	SDL_Rect dst;
};