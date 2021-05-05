#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Button.h"
#include "Textbox.h"
#include <fstream>
const int mapRange = 4;
const int EDGE = 160;
const int OFFSET_BOTTOM = 40;

class Textbox;

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
	void preLoad(SDL_Color color);
	void saveHighScore();
	int score;
	int hScore;
private:
	int map[mapRange][mapRange];
	SDL_Texture* whiteTile;
	//SDL_Texture* blackTile;
	SDL_Rect src, dst;
	int lastRow, lastColumn;

	SDL_Texture* scoreTexture;

	Textbox* preLoadText;
	SDL_Texture* preLoadBackground;
	//Button* pause;
};

