#pragma once
#include <SDL.h>
#include <SDL_image.h>
#undef main  //sdl_main has already defined in sdl.h, that's why we need this line
#include <iostream>
using namespace std;
const int WIDTH = 1280;
const int HEIGHT = 720;


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
	static SDL_Renderer* renderer;
private:
	SDL_Texture* background;
	bool isRunning;
	SDL_Rect destR;
	SDL_Window* window;
};