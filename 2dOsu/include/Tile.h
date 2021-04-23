#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

const int mapRange = 4;
const int EDGE = 160;
const int OFFSET_BOTTOM = 40;

class Tile {
public:
	Tile();
	~Tile();
	void render();
	void update();
	void setBlackKey(bool isClick = false);
	bool check(const int& mouseX, const int& mouseY);
private:
	int map[mapRange][mapRange];
	SDL_Texture* whiteTile;
	SDL_Texture* blackTile;
	SDL_Rect src, dst;
	int lastRow, lastColumn;
};