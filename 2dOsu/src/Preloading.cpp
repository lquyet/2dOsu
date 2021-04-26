#include "../include/Preloading.h"
#include "../include/Texture.h"

extern TTF_Font* font30;
extern SDL_Color pointColor;
extern Game* game;

Preloading::Preloading() {
	preloadBackground = Texture::loadTexture("assets/backgroundBlack.png");
	SDL_SetTextureAlphaMod(preloadBackground, 10);
	startTicks = SDL_GetTicks();
}

Preloading::~Preloading() {

}

void Preloading::render() {
	SDL_RenderCopy(Game::renderer, preloadBackground, NULL, NULL);
	count->render();
}

void Preloading::update() {
	uint32_t sec = SDL_GetTicks() - startTicks;
	if (sec >= 3000) {
		game->gameState = 1; //Ingame
		return;
	} 
	count->update(to_string(3 - sec/1000), font30, pointColor);
	center();
}

void Preloading::center() {
	count->dst.x = WIDTH / 2 - count->dst.w / 2;
	count->dst.y = HEIGHT / 2 - count->dst.h / 2;
}