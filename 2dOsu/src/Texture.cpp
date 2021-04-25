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

SDL_Texture* Texture::renderText(const std::string& message, TTF_Font* font,
	SDL_Color color) {
	SDL_Surface* sf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (sf == NULL) {
		TTF_CloseFont(font);
		cout << "CREATING SURFACE ERROR - TTF FONT   " << TTF_GetError() <<  endl;
		return NULL;
	}
	SDL_Texture* tx = SDL_CreateTextureFromSurface(Game::renderer, sf);
	if (tx == NULL) {
		cout << "CREATING TEXTURE ERROR - TTF FONT    " << TTF_GetError() << endl;
	}
	//int w, h;
	//SDL_QueryTexture(tx, NULL, NULL, &w, &h);
	//cout << w << " " << h << endl;
	SDL_FreeSurface(sf);
	return tx;
}
