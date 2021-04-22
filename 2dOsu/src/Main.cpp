#include "../include/Game.h"

Game* game = NULL;
SDL_Renderer* Game::renderer = NULL;
Tile* tile = NULL;
const int FPS = 60;
const int frameDelay = 1000 / FPS;


int main() {
	srand(time(NULL)); //init random for setBackKey function in Tile class
	Uint32 frameStart;
	int frameTime;
	game = new Game();
	game->init("Osu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, true);

	while (game->running()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		//game->render();
		frameTime = SDL_GetTicks() - frameStart;
		//limit fps
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);

	}
	game->clean();
	return 0;
}