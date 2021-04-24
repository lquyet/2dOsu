#include "../include/Game.h"
#include "../include/StartScreen.h"

Game* game = NULL;
SDL_Renderer* Game::renderer = NULL;
int Game::gameState = 0;
Tile* tile = NULL;

const int FPS = 200;
const int frameDelay = 1000 / FPS;


int main() {
	srand(time(NULL)); //init random for setBackKey function in Tile class
	Uint32 frameStart;
	int frameTime;
	game = new Game();
	game->init("Super Hard Osu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, false);
	while (game->running()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		//limit fps
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);

	}
	game->clean();
	return 0;
}