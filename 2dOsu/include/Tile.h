#pragma once
#include <SDL.h>
#include <iostream>
using namespace std;

const int mapRange = 3;
class Tile {
public:
	Tile();
	~Tile();
	void render();
	void update();
	void setBlackKey();
private:
	int map[mapRange][mapRange];
	SDL_Rect tile;
};