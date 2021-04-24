#include "../include/Button.h"

extern Game* game;

Button::Button(std::string pathToImage,const int &x,const int &y) {
	button = Texture::loadTexture(pathToImage.c_str());
	SDL_QueryTexture(button, NULL, NULL, &bWidth, &bHeight);
	dst.w = bWidth;
	dst.h = bHeight;
	dst.x = x;
	dst.y = y;
}

Button::Button() {

}

Button::~Button() {

}

void Button::focus(bool focus) {
	bFocus = focus;
}

void Button::render() {
	SDL_RenderCopy(Game::renderer, button, NULL, &dst);
}

void Button::update() {
	//check if cursor point to button
	int x = game->getMouseX();
	int y = game->getMouseY();
	if ((dst.x <= x && x <= dst.x + dst.w) && (dst.y <= y && y <= dst.y + dst.h)) {
		bFocus = true;
	}
	else {
		bFocus = false;
	}

	if (bFocus == true) {
		SDL_SetTextureColorMod(button, focusColor.r, focusColor.g, focusColor.b);
	}
	else {
		SDL_SetTextureColorMod(button, 0, 0, 0);
	}
}