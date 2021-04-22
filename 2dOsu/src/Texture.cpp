#include "../include/Texture.h"

SDL_Texture* Texture::loadTexture(const char* path) {
	SDL_Texture* tx = NULL;
	SDL_Surface* tempSF = IMG_Load(path); //load png file
	if (tempSF != NULL) {
		tx = SDL_CreateTextureFromSurface(Game::renderer, tempSF);
		if (tx == NULL) {
			cout << SDL_GetError() << endl;
		}
	}
	else {
		cout << SDL_GetError() << endl;
	}
	return tx;
}

void Texture::Draw(SDL_Texture* tx, SDL_Rect src, SDL_Rect dst) {
	SDL_RenderCopy(Game::renderer, tx, &src, &dst);
}
//open and close font each time, not effectively, just give a try
/*
SDL_Texture* Texture::renderText(const std::string& message, const std::string& fontFile,
	SDL_Color color, int fontSize, SDL_Renderer* renderer) {

}
*/