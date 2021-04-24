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
	blackTile = Texture::loadTexture("assets/tile.png");

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
			dst.y =  HEIGHT - mapRange * EDGE + ViewportY + i * 160 - OFFSET_BOTTOM; //row

			switch (type) {
			case 0:
				SDL_SetTextureColorMod(whiteTile, 173, 197, 183);
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

void Tile::setBlackKey(bool isClick) {
	int rRow, rCol;
	if (isClick == true) {
		do {
			rRow = rand() % mapRange;
			rCol = rand() % mapRange;
		} while (map[rRow][rCol] == 1 || (lastRow == rRow && lastColumn == rCol));
	}
	else {
		do {
			rRow = rand() % mapRange;
			rCol = rand() % mapRange;
		} while (map[rRow][rCol] == 1);
	}
	map[rRow][rCol] = 1;  // clickable, change color to black
	cout << "(" << rRow << ":" << rCol << ")" << "       " << "(" << lastRow << ":" << lastColumn << ")" << endl;
}

bool Tile::check(const int& mouseX, const int& mouseY) {
	// exchange the origin 

	int tempX = mouseX - ViewportX;
	int tempY = mouseY - (HEIGHT - mapRange * EDGE + ViewportY - OFFSET_BOTTOM);

	if (tempX < 0 || tempY < 0 || tempX > ViewportWidth || tempY > mapRange * EDGE) return true;  //outside gamezone

	int row = floor(tempY / EDGE);
	int column = floor(tempX / EDGE);
	if (map[row][column] == 1) {
		map[row][column] = 0;
		lastRow = row;
		lastColumn = column;
		setBlackKey(true);
		return true;
	}
	return false;

}