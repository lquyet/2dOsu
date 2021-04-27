#include "../include/Textbox.h"

Textbox::Textbox(std::string msg, TTF_Font* font, SDL_Color color, const int &x, const int &y) {
	text = Texture::renderText(msg, font, color);
	SDL_QueryTexture(text, NULL, NULL, &dst.w, &dst.h);
	dst.x = x;
	dst.y = y;
	//tFont = font;
}

Textbox::~Textbox() {
	SDL_DestroyTexture(text);
}

void Textbox::render() {
	SDL_RenderCopy(Game::renderer, text, NULL, &dst);
}

void Textbox::update(std::string msg, TTF_Font* font, SDL_Color color) {
	text = Texture::renderText(msg, font, color);
	SDL_QueryTexture(text, NULL, NULL, &dst.w, &dst.h);
}

//hasnt worked yet
void Textbox::scoreEffect(TTF_Font* fontList[10], std::string msg, SDL_Color color) {
	for (int j = 9; j >= 0; j--) {
		text = Texture::renderText(msg, fontList[j], color);
		SDL_QueryTexture(text, NULL, NULL, &dst.w, &dst.h);
	}
}

void Textbox::moveX(int distance) {
	dst.x += distance;
}

void Textbox::moveY(int distance) {
	dst.y += distance;
}

//vertically centerize
void Textbox::center(const int& x) {  
	dst.x = x - dst.w / 2;
}

void Textbox::center(const int& x, const int& y) {
	dst.x = x - dst.w / 2;
	dst.y = y - dst.h / 2;
}