#pragma once
#include "Texture.h"
#include <functional>

class Button {
public:
	Button(std::string pathToImage, const int &x, const int &y);
	Button();
	~Button();
	void focus(bool focus);
	void update();
	void render();
	void center(const int &x);
	//void onClick(void func());
	SDL_Rect dst;
	SDL_Color focusColor;
	bool bFocus;
	SDL_Texture* focusButton;  //use instead of focusColor, more effects
private:
	int bWidth;
	int bHeight;
	SDL_Texture* button;
	SDL_Texture* tempButton;

};