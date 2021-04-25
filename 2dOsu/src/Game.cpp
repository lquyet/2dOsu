#include "../include/Game.h"

extern Tile* tile;
extern Timer* countdown;
SDL_Texture* background = NULL;
SDL_Texture* image = NULL;
StartScreen* intro = NULL;
SDL_Color color = { 255,255,255,255 };
SDL_Rect dst = { 0,0,90,14 };
Button* play = NULL;

extern Button* pause;

Game::Game() {

}

Game::~Game() {

}

enum State {
	Intro = 0,
	Ingame = 1,
	Option = 2,
	Preloading = 3,
	End = 4
};


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flag = 0;
	if (fullscreen) flag = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "SDL Init" << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
		if (window != NULL) {
			cout << "Window created" << endl;
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer != NULL) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				cout << "Renderer created" << endl;
				isRunning = true;
			}
			else {
				isRunning = false;
				clean();
			}
		}
		else {
			isRunning = false;
			return;
		}
	}
	else {
		isRunning = false;
		return;
	}
	if (TTF_Init() != 0) {
		cout << "TTF ERROR" << endl;
		isRunning = false;
	}
	//setViewport(ViewportX, ViewportY, ViewportHeight, ViewportWidth);
	//intro = new StartScreen();
	tile = new Tile();
	//background = Texture::loadTexture("assets/backgroundBlack.png");
	//TTF_Font* font = TTF_OpenFont("font/Bariol.ttf", 14);
	//image = Texture::renderText("HELLO WORLD", font, color, 14);
	//TTF_CloseFont(font);
	//gameState = 0;

}

void Game::update() {
	SDL_GetMouseState(&mouseX, &mouseY); //update mouse position
	//cout << "X: " << mouseX << "  " << "Y: " << mouseY << endl;
	/*
	switch (gameState) {
	case Intro:
		intro->update();
		break;
	case Ingame:
		tile->update();
	case Option:
		break;
	case Preloading:
		break;
	case End:
		break;
	default:
		break;
	}
	*/
	tile->update();
	
}

void Game::handleEvents() {
	SDL_Event e;
	SDL_PollEvent(&e);
	//check one per time
	switch (e.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mouseX, &mouseY);
		if (countdown->isPaused == false && !(tile->check(mouseX, mouseY))) {
			isRunning = false;
		}
		if (pause->bFocus == true) {
			if (countdown->isPaused == false) {
				countdown->pause();
				//countdown->isPaused == true;
			}
			else {
				//countdown->isPaused == false;
				countdown->resume();
			}
		}
		break;
	default:
		break;
	}

}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	cout << "Quit!" << endl;
	SDL_Quit();
}

void Game::render() {
	//clear previous renderer if existed
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, background, NULL, NULL);
	//SDL_RenderCopy(renderer, image, NULL, &dst);
	/*
	switch (gameState) {
	case Intro:
		intro->render();
	case Ingame:
		tile->render();
	case Option:
		break;
	case Preloading:
		break;
	case End:
		break;
	default:
		break;
	}
	*/
	tile->render();
	
	SDL_RenderPresent(renderer);
}

bool Game::running() {
	return isRunning;
}

void Game::setViewport(const int& Vx, const int& Vy, const int& Vh, const int& Vw) {
	viewport.x = Vx;
	viewport.y = Vy;
	viewport.h = Vh;
	viewport.w = Vw;
	SDL_RenderSetViewport(renderer, &viewport);
}

