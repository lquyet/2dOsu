#include "../include/Tile.h"
#include "../include/Texture.h"
#include "../include/Game.h"

Tile::Tile() {
	//empty the map
	for (int i = 0; i < mapRange; i++) {
		for (int j = 0; j < mapRange; j++) {
			map[i][j] = 0;
		}
	}
	for (int i = 0; i < mapRange - 1; i++) setBlackKey();
	whiteTile = Texture::loadTexture("assets/whiteTile.png");
	blackTile = Texture::loadTexture("assets/blackTile.png");

	src.x = src.y = 0;
	src.w = dst.w = EDGE;
	src.h = dst.h = EDGE;
	dst.x = 0;
	dst.y = 0;

}

Tile::~Tile() {

}

void Tile::render() {
	int type;
	for (int i = 0; i < mapRange; i++) {
		for (int j = 0; j < mapRange; j++) {
			type = map[i][j];

			dst.x =  ViewportX + j * 160; //column
			dst.y =  160 + ViewportY + i * 160 - 40; //row

			switch (type) {
			case 0:
				Texture::Draw(whiteTile, src, dst);
				break;
			case 1:
				Texture::Draw(blackTile, src, dst);
				break;
			default:
				break;
			}
		}
	}
}

void Tile::update() {
	//check mouse click

}

void Tile::setBlackKey() {
	int rRow, rCol;
	do {
		rRow = rand() % mapRange;
		rCol = rand() % mapRange;
	} while (map[rRow][rCol] == 1);
	map[rRow][rCol] = 1;  // clickable, change color to black
}