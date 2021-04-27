#include "../include/Tile.h"
#include "../include/Texture.h"
#include "../include/Game.h"
#include "../include/Textbox.h"
#include "../include/Timer.h"
#include <string>
#include <fstream>
#include <SDL_thread.h>
class Textbox;
extern Music* music;
extern Game* game;
Button* pause = NULL;
TTF_Font* font30 = NULL;
SDL_Color fontColor = { 0,0,0 };
Textbox* scoreBox = NULL;
Textbox* hiScore = NULL;
Textbox* hiScorePoint = NULL;
Textbox* timeText = NULL;
Textbox* point = NULL;
SDL_Color pointColor = { 28,135,179 };
SDL_Color fadeColor = { 50, 168, 82 };
SDL_Color tempFade = { 50, 168, 82 };
Timer* countdown = NULL;
Textbox* countdownText = NULL;
uint32_t alpha[mapRange][mapRange];
extern EndScreen* endScreen;
SDL_Color wrong = { 200, 0, 0 };

TTF_Font* fontList[10]; //score effect  from size 30 -> 50, distance = 2



Tile::Tile() {
	//empty the map
	for (int i = 0; i < mapRange; i++) {
		for (int j = 0; j < mapRange; j++) {
			map[i][j] = 0;
			//alpha
			alpha[i][j] = 255;
		}
	}
	for (int i = 0; i < mapRange - 1; i++) setBlackKey();
	whiteTile = Texture::loadTexture("assets/whiteTile.png");
	//blackTile = Texture::loadTexture("assets/tile.png");

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

	countdown = new Timer(5);
	countdownText = new Textbox(to_string(countdown->getTimeLeft()), fontList[9], pointColor, 0, 50);
	countdownText->center(ViewportX + EDGE / 2 + (mapRange - 1) * EDGE);

	preLoadText = NULL;
	preLoadBackground = NULL;
	//SDL_SetRenderDrawColor(Game::renderer, 199, 193, 181, 255);
}

Tile::~Tile() {
	TTF_CloseFont(font30);
	pause->~Button();
	scoreBox->~Textbox();
	hiScore->~Textbox();
	hiScorePoint->~Textbox();
	timeText->~Textbox();
	point->~Textbox();
	countdown->~Timer();
	countdownText->~Textbox();
	for (int i = 0; i < 10; i++) {
		TTF_CloseFont(fontList[i]);
	}
}

void Tile::render() {
	//render tiles
	int type;
	for (int i = 0; i < mapRange; i++) {
		for (int j = 0; j < mapRange; j++) {
			type = map[i][j];

			dst.x =  ViewportX + j * EDGE; //column
			dst.y =  HEIGHT - mapRange * EDGE + ViewportY + i * 160 - OFFSET_BOTTOM; //row

			switch (type) {
			case 0:
				SDL_SetTextureAlphaMod(whiteTile, 255);
				SDL_SetTextureColorMod(whiteTile, 255, 255, 255);
				Texture::Draw(whiteTile, src, dst);
				break;
			case 1:
				SDL_SetTextureAlphaMod(whiteTile, 255);
				SDL_SetTextureColorMod(whiteTile, 100, 100, 100);
				Texture::Draw(whiteTile, src, dst);
				//Texture::Draw(blackTile, src, dst);
				break;
			case 2:  //fucked up with fading effect
				/*
				tempFade.r+=3;
				tempFade.g+=3;
				tempFade.b+=3;
				if (tempFade.r > 255) tempFade.r = 255;
				if (tempFade.g > 255) tempFade.g = 255;
				if (tempFade.b > 255) tempFade.b = 255;
				SDL_SetTextureColorMod(whiteTile, tempFade.r, tempFade.g, tempFade.b);
				Texture::Draw(whiteTile, src, dst);
				cout << (int)tempFade.r << endl;
				//cout << tempFade.r << " " << tempFade.g << " " << tempFade.b << endl;
				if (tempFade.r >= 254 || tempFade.g >= 254 || tempFade.b >= 254) {
					map[i][j] = 0;
					tempFade = fadeColor;
				}
				*/
				SDL_SetTextureColorMod(whiteTile, fadeColor.r, fadeColor.g, fadeColor.b);
				SDL_SetTextureAlphaMod(whiteTile, alpha[i][j]);
				Texture::Draw(whiteTile, src, dst);
				alpha[i][j] -= 2;
				if (alpha[i][j] <= 6) {
					map[i][j] = 0;
					alpha[i][j] = 255;
				}
				//cout << alpha << endl;
				//SDL_SetTextureAlphaMod(whiteTile, 255);
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
		} while (map[rRow][rCol] == 1 || map[rRow][rCol] == 2 || (lastRow == rRow && lastColumn == rCol));
	}
	else {
		do {
			rRow = rand() % mapRange;
			rCol = rand() % mapRange;
		} while (map[rRow][rCol] == 1 || map[rRow][rCol] == 2);
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
			map[row][column] = 2;
			score++;
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
	

void Tile::preLoad(SDL_Color color) {
	//this function with run synchronously, so i have to create a (new) temporary event handler in this 3-second period
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) game->setRunningState(false);
	}
	TTF_Font* font = TTF_OpenFont("font/Bariol.ttf", 200);
	preLoadBackground = Texture::loadTexture("assets/backgroundBlack.png");
	SDL_SetTextureAlphaMod(preLoadBackground, 100);

	int timer = 3; //seconds
	uint32_t start = SDL_GetTicks();
	preLoadText = new Textbox(to_string(timer), font, color, 0, HEIGHT / 2);
	preLoadText->center(WIDTH / 2, HEIGHT/2);
	uint32_t tick = SDL_GetTicks() - start;
	while (tick < timer*1000) {
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, preLoadBackground, NULL, NULL);
		preLoadText->update(to_string(timer - tick / 1000), font, color);
		preLoadText->render();
		SDL_RenderPresent(Game::renderer);
		tick = SDL_GetTicks() - start;
	}
	TTF_CloseFont(font);
}