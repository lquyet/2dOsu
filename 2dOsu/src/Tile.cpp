#include "../include/Tile.h"
#include "../include/Texture.h"
#include "../include/Game.h"
#include "../include/Textbox.h"
#include "../include/Timer.h"
#include <string>
#include <fstream>

extern Music* music;
Button* pause = NULL;
TTF_Font* font30 = NULL;
SDL_Color fontColor = { 0,0,0 };
Textbox* scoreBox = NULL;
Textbox* hiScore = NULL;
Textbox* hiScorePoint = NULL;
Textbox* timeText = NULL;
Textbox* point = NULL;
SDL_Color pointColor = { 28,135,179 };
Timer* countdown = NULL;
Textbox* countdownText = NULL;

TTF_Font* fontList[10]; //score effect  from size 30 -> 50, distance = 2

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

	score = 0;
	font30 = TTF_OpenFont("font/Bariol.ttf", 30);
	pause = new Button("assets/pauseIcon2.png", 40, 50);
	pause->dst.w = 80;
	pause->dst.h = 80;
	pause->focusColor = { 200,0,0 };

	//get highest score
	fstream hiScoreFile;
	hiScoreFile.open("highScore.txt");
	hiScoreFile >> hScore;
	hiScoreFile.close();
	for (int i = 0; i < 10; i++) {
		fontList[i] = TTF_OpenFont("font/Bariol.ttf", 30 + i * 5);
	}
	scoreBox = new Textbox("Score", font30, fontColor, 0, 10);
	scoreBox->center(ViewportX + mapRange / 2 * EDGE);

	hiScore = new Textbox("Hi - Score", font30, fontColor, 0, 10); 
	hiScore->center(ViewportX + EDGE / 2);

	hiScorePoint = new Textbox(to_string(hScore), fontList[9], pointColor, 0, 50);
	hiScorePoint->center(ViewportX + EDGE / 2);

	timeText = new Textbox("Time", font30, fontColor, 0, 10);
	timeText->center(ViewportX + EDGE / 2 + (mapRange - 1) * EDGE);

	point = new Textbox(to_string(score), fontList[9], pointColor, 0, 50);
	point->center(ViewportX + mapRange / 2 * EDGE);

	countdown = new Timer(40);
	countdownText = new Textbox(to_string(countdown->getTimeLeft()), fontList[9], pointColor, 0, 50);
	countdownText->center(ViewportX + EDGE / 2 + (mapRange - 1) * EDGE);
}

Tile::~Tile() {
	TTF_CloseFont(font30);
}

void Tile::render() {
	//render tiles
	int type;
	for (int i = 0; i < mapRange; i++) {
		for (int j = 0; j < mapRange; j++) {
			type = map[i][j];

			dst.x =  ViewportX + j * 160; //column
			dst.y =  HEIGHT - mapRange * EDGE + ViewportY + i * 160 - OFFSET_BOTTOM; //row

			switch (type) {
			case 0:
				//SDL_SetTextureColorMod(whiteTile, 173, 197, 183);
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

	pause->render();
	//render score
	scoreBox->render();
	hiScore->render();
	timeText->render();
	point->render();
	hiScorePoint->render();
	countdownText->render();
}

void Tile::update() {
	//check mouse click
	pause->update();
	//scoreBox->update("Score", font, fontColor);
	if (countdown->isPaused == false) {
		point->center(ViewportX + mapRange / 2 * EDGE);
		hiScorePoint->center(ViewportX + EDGE / 2);
		countdownText->update(to_string(countdown->getTimeLeft()), fontList[9], pointColor);
		countdownText->center(ViewportX + EDGE / 2 + (mapRange - 1) * EDGE);
	}
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
	if (!countdown->isPaused) {
		int tempX = mouseX - ViewportX;
		int tempY = mouseY - (HEIGHT - mapRange * EDGE + ViewportY - OFFSET_BOTTOM);

		if (tempX < 0 || tempY < 0 || tempX > ViewportWidth || tempY > mapRange * EDGE) return true;  //outside gamezone

		int row = floor(tempY / EDGE);
		int column = floor(tempX / EDGE);
		if (map[row][column] == 1) {
			int note = rand() % 16;
			Mix_PlayChannel(-1, music->chunkList[note], 0);
			map[row][column] = 0;
			score++;
			if (score == 10) point->moveX(-15);
			else if (score == 100) point->moveX(-15);
			point->update(to_string(score), fontList[9], pointColor);
			lastRow = row;
			lastColumn = column;
			setBlackKey(true);
			return true;
		}
		else {
			if (score > hScore) {
				hScore = score;
				score = 0;
				ofstream ofs("highScore.txt", std::ofstream::trunc);
				ofs << hScore;
				ofs.close();
			}
		}
		return false;
	}
	return true;
}
	

