#include "../include/Tile.h"

Tile::Tile() {
	//empty the map
	for (int i = 0; i < mapRange; i++) {
		for (int j = 0; j < mapRange; j++) {
			map[i][j] = 0;
		}
	}
	for (int i = 0; i < mapRange; i++) setBlackKey();

}

Tile::~Tile() {

}

void Tile::render() {

}

void Tile::update() {

}

void Tile::setBlackKey() {
	int rRow, rCol;
	do {
		rRow = rand() % mapRange;
		rCol = rand() % mapRange;
	} while (map[rRow][rCol] == 1);
	map[rRow][rCol] = 1;  // clickable, change color to black
}