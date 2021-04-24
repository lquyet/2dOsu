#pragma once
#include "Game.h";

class Texture {
public:
	static SDL_Texture* loadTexture(const char* path);
	static void Draw(SDL_Texture* tx, SDL_Rect src, SDL_Rect dst);
	static SDL_Texture* renderText(const std::string& message, TTF_Font* font,
		SDL_Color color); // pass a TTF_Font* is better, implement latter
};