#include "../include/Tile.h"
#include "../include/Texture.h"
#include "../include/Game.h"
#include "../include/Textbox.h"
#include "../include/Timer.h"
#include <string>

class Textbox;
extern Music* music;
extern Game* game;
extern EndScreen* endScreen;

Button* pause = NULL;

TTF_Font* font30 = NULL;

SDL_Color fontColor = { 0,0,0 };
SDL_Color pointColor = { 28,135,179 };
SDL_Color hiScoreColor = { 106, 113, 125 };
SDL_Color fadeGrayTileColor = { 50, 168, 82 };
SDL_Color timerColor = { 227, 140, 34 };
SDL_Color wrong = { 200, 0, 0 };
SDL_Color bonusTime = { 235, 207, 52 };
SDL_Color bonusPoint = { 52, 235, 226 };

Textbox* scoreBox = NULL;
Textbox* hiScore = NULL;
Textbox* hiScorePoint = NULL;
Textbox* timeText = NULL;
Textbox* point = NULL;
Textbox* countdownText = NULL;

Timer* countdown = NULL;

uint32_t alpha[mapRange][mapRange];

TTF_Font* font75 = NULL;

void fadeEffect(SDL_Texture* tx, SDL_Color color, int map[mapRange][mapRange], uint32_t alpha[mapRange][mapRange], const int& row, const int& col, const SDL_Rect &src,const SDL_Rect &dst);

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
	pause = new Button("assets/pauseIcon.png", 40, 50);
	pause->dst.w = 80;
	pause->dst.h = 80;
	pause->focusColor = { 200,0,0 };

	//get highest score
	fstream hiScoreFile;
	hiScoreFile.open("highScore.txt");
	hiScoreFile >> hScore;
	hiScoreFile.close();

	font75 = TTF_OpenFont("font/Bariol.ttf", 75);

	scoreBox = new Textbox("Score", font30, fontColor, 0, 10);
	scoreBox->center(ViewportX + mapRange / 2 * EDGE);

	hiScore = new Textbox("Hi - Score", font30, fontColor, 0, 10); 
	hiScore->center(ViewportX + EDGE / 2);

	hiScorePoint = new Textbox(to_string(hScore), font75, hiScoreColor, 0, 50);
	hiScorePoint->center(ViewportX + EDGE / 2);

	timeText = new Textbox("Time", font30, fontColor, 0, 10);
	timeText->center(ViewportX + EDGE / 2 + (mapRange - 1) * EDGE);

	point = new Textbox(to_string(score), font75, pointColor, 0, 50);
	point->center(ViewportX + mapRange / 2 * EDGE);

	countdown = new Timer(20);
	countdownText = new Textbox(to_string(countdown->getTimeLeft()), font75, timerColor, 0, 50);
	countdownText->center(ViewportX + EDGE / 2 + (mapRange - 1) * EDGE);

	preLoadText = NULL;
	preLoadBackground = NULL;
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
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
	TTF_CloseFont(font75);
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
			case 0: //raw white tile
				SDL_SetTextureAlphaMod(whiteTile, 255);
				SDL_SetTextureColorMod(whiteTile, 255, 255, 255);
				Texture::Draw(whiteTile, src, dst);
				break;
			case 1: //raw black (actually gray) tile
				SDL_SetTextureAlphaMod(whiteTile, 255);
				SDL_SetTextureColorMod(whiteTile, 100, 100, 100);
				Texture::Draw(whiteTile, src, dst);
				break;
			case 2:  
				fadeEffect(whiteTile, fadeGrayTileColor, map, alpha, i, j, src, dst);
				break;
			case 3: // raw orange tile
				SDL_SetTextureAlphaMod(whiteTile, 255);
				SDL_SetTextureColorMod(whiteTile, bonusTime.r, bonusTime.g, bonusTime.b);
				Texture::Draw(whiteTile, src, dst);
				break;
			case 4: // raw blue (?) tile
				SDL_SetTextureAlphaMod(whiteTile, 255);
				SDL_SetTextureColorMod(whiteTile, bonusPoint.r, bonusPoint.g, bonusPoint.b);
				Texture::Draw(whiteTile, src, dst);
				break;
			case 5: //fading orange tile
				fadeEffect(whiteTile, bonusTime, map, alpha, i, j, src, dst);
				break;
			case 6: //fading blue (?) tile
				fadeEffect(whiteTile, bonusPoint, map, alpha, i, j, src, dst);
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
		countdownText->update(to_string(countdown->getTimeLeft()), font75, timerColor);
		countdownText->center(ViewportX + EDGE / 2 + (mapRange - 1) * EDGE);
	}
}

void Tile::setBlackKey(bool isClick) {
	int rRow, rCol;
	if (isClick == true) {
		do {
			rRow = rand() % mapRange;
			rCol = rand() % mapRange;
		} while (map[rRow][rCol] != 0 || (lastRow == rRow && lastColumn == rCol));
	}
	else {
		do {
			rRow = rand() % mapRange;
			rCol = rand() % mapRange;
		} while (map[rRow][rCol] != 0 || map[rRow][rCol] == 3);
	}

	//do randomization
	int r = rand() % 40;
	if (r < 2) map[rRow][rCol] = 3;  //just for 10% getting a bonus time tile
	else if (r == 2 || r == 3) map[rRow][rCol] = 4; // 10% getting a bonus point
	else map[rRow][rCol] = 1;

}

bool Tile::check(const int& mouseX, const int& mouseY) {
	// exchange the origin 
	if (!countdown->isPaused) {
		int tempX = mouseX - ViewportX;
		int tempY = mouseY - (HEIGHT - mapRange * EDGE + ViewportY - OFFSET_BOTTOM);

		if (tempX < 0 || tempY < 0 || tempX > ViewportWidth || tempY > mapRange * EDGE) return true;  //outside gamezone

		int row = floor(tempY / EDGE);
		int column = floor(tempX / EDGE);
		if (map[row][column] != 0 && map[row][column] != 2 && map[row][column] != 5) {
			int note = rand() % 16;
			Mix_PlayChannel(-1, music->chunkList[note], 0);
			switch (map[row][column])
			{
			case 3:
				countdown->addBonusTime(5);
				map[row][column] = 5;
				break;
			case 4:
				score += 3;
				map[row][column] = 6;
				break;
			default:
				map[row][column] = 2;
				break;
			}
			score++;
			point->update(to_string(score), font75, pointColor);
			lastRow = row;
			lastColumn = column;
			setBlackKey(true);
			return true;
		}
		else {
			if (score > hScore) {
				alpha[row][column] = 255;
				hScore = score;
				//score = 0;
				saveHighScore();
			}
		}
		return false;
	}
	return true;
}
	

void Tile::preLoad(SDL_Color color) {
	//this function with run synchronously, so i have to create a (new) temporary event handler in this 3-second period
	SDL_Event e;
	SDL_Color guideTextColor1 = pointColor;
	SDL_Color guideTextColor2 = bonusTime; 
	SDL_Color guideTextColor3 = bonusPoint;
	TTF_Font* font = TTF_OpenFont("font/Bariol.ttf", 200);
	TTF_Font* guide = TTF_OpenFont("font/Bariol.ttf", 50);
	Textbox* guideTime = new Textbox("This color will give you more time", guide, guideTextColor2, 0, 0);
	guideTime->center(WIDTH / 2, HEIGHT / 2 + 100);
	Textbox* guidePoint = new Textbox("This color will give you more points", guide, guideTextColor3, 0, 0);
	guidePoint->center(WIDTH / 2, HEIGHT / 2 + 150);
	preLoadBackground = Texture::loadTexture("assets/backgroundBlack.png");
	SDL_SetTextureAlphaMod(preLoadBackground, 100);
	int timer = 4; //seconds
	uint32_t start = SDL_GetTicks();
	preLoadText = new Textbox(to_string(timer), font, color, 0, HEIGHT / 2);
	preLoadText->center(WIDTH / 2, HEIGHT/2);
	uint32_t tick = SDL_GetTicks() - start;
	while (tick < timer*1000) {
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			game->setRunningState(false);
			return;
		}
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, preLoadBackground, NULL, NULL);
		if (tick >= 3000) {
			preLoadText->update("Click all non-white tiles in 20 seconds", guide, guideTextColor1);
			preLoadText->center(WIDTH / 2, HEIGHT / 2);
			guideTime->render();
			guidePoint->render();
		} else preLoadText->update(to_string(timer - tick / 1000 - 1), font, color);
		preLoadText->render();
		SDL_RenderPresent(Game::renderer);
		tick = SDL_GetTicks() - start;
	}
	guideTime->~Textbox();
	guidePoint->~Textbox();
	TTF_CloseFont(font);
	TTF_CloseFont(guide);
}

void fadeEffect(SDL_Texture* tx, SDL_Color color,int map[mapRange][mapRange],uint32_t alpha[mapRange][mapRange], const int& row, const int& col, const SDL_Rect &src, const SDL_Rect &dst) {
	SDL_SetTextureColorMod(tx, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(tx, alpha[row][col]);
	Texture::Draw(tx, src, dst);
	alpha[row][col] -= 2;
	if (alpha[row][col] <= 6) {
		map[row][col] = 0;
		alpha[row][col] = 255;
	}
}

void Tile::saveHighScore() {
	ofstream ofs("highScore.txt", std::ofstream::trunc);
	ofs << hScore;
	ofs.close();
}