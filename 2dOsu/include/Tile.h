#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Button.h"
const int mapRange = 4;
const int EDGE = 160;
const int OFFSET_BOTTOM = 40;

int fade(void* data);

class Tile {
public:
	Tile();
	~Tile();
	void render();
	void update();
	void setBlackKey(bool isClick = false);
	bool check(const int& mouseX, const int& mouseY);
	int getLastRow() { return lastRow; }
	int getLastCol() { return lastColumn; }

private:
	int map[mapRange][mapRange];
	SDL_Texture* whiteTile;
	//SDL_Texture* blackTile;
	SDL_Rect src, dst;
	int lastRow, lastColumn;
	int score;
	SDL_Texture* scoreTexture;
	int hScore;
	//Button* pause;
};

