#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int mapRange = 4;
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