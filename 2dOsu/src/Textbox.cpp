#include "../include/Textbox.h"

Textbox::Textbox(std::string msg, TTF_Font* font, SDL_Color color, const int &x, const int &y) {
	text = Texture::renderText(msg, font, color);
	SDL_QueryTexture(text, NULL, NULL, &dst.w, &dst.h);
	dst.x = x;
	dst.y = y;
}

Textbox::~Textbox() {

}

void Textbox::render() {
	SDL_RenderCopy(Game::renderer, text, NULL, &dst);
}

void Textbox::update(std::string msg, TTF_Font* font, SDL_Color color) {
	text = Texture::renderText(msg, font, color);
	SDL_QueryTexture(text, NULL, NULL, &dst.w, &dst.h);
}

void Textbox::scoreEffect() {
	
}