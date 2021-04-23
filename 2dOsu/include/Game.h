#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Tile.h"
#undef main  //sdl_main has already defined in sdl.h, that's why we need this line
using namespace std;


const int WIDTH = 1280;
const int HEIGHT = 800;
const int ViewportWidth = 680;
const int ViewportHeight = HEIGHT;
const int ViewportX = WIDTH / 2 - ViewportWidth / 2;  //center the viewport
const int ViewportY = 0;

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
	void setViewport(const int& Vx, const int& Vy, const int& Vh, const int& Vw);
	static SDL_Renderer* renderer;
private:
	SDL_Texture* background;
	bool isRunning;
	SDL_Window* window;
	SDL_Rect viewport;
};