#include "../include/Game.h"

extern Tile* tile;
extern Timer* countdown;
SDL_Color c = { 28,135,179 };    // == point color
Music* music = NULL;
StartScreen* intro = NULL;
//SDL_Color color = { 255,255,255,255 };
SDL_Rect dst = { 0,0,90,14 };
extern Button* pause;
EndScreen* endScreen = NULL;
OptionMenu* optionMenu = NULL;
const string chunks[16] = { "a6", "a7", "a8", "c6", "c7", "c8", "c9", "d6", "d7", "d8", "f6", "f7", "f8", "g6", "g7", "g8" };

Game::Game() {

}

Game::~Game() {

}

enum State {
	Intro = 0,
	Ingame = 1,
	End = 2,
	Option = 3
};


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flag = 0;
	playerCharacter = DEFAULT;
	if (fullscreen) flag = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "SDL Init" << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
		if (window != NULL) {
			cout << "Window created" << endl;
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer != NULL) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				cout << "Renderer created" << endl;
				isRunning = true;
			}
			else {
				isRunning = false;
				clean();
			}
		}
		else {
			isRunning = false;
			return;
		}
	}
	else {
		isRunning = false;
		return;
	}
	if (TTF_Init() != 0) {
		cout << "TTF ERROR" << endl;
		isRunning = false;
	}

	gameState = Intro;
	intro = new StartScreen();
	optionMenu = new OptionMenu();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << Mix_GetError() << endl;
	}
	if (Mix_Init(MIX_INIT_MP3) < 0) {  //damn i fucked up with this for a long time. forgot .dll files @@
		cout << Mix_GetError() << endl;
	}

	else {
		music = new Music();
		music->background = Mix_LoadMUS("assets/audio/backgroundMusic.mp3");
		if (music->background == NULL) cout << Mix_GetError() << endl;
		else Mix_PlayMusic(music->background, -1);

		//load chunks

		for (int i = 0; i < 16; i++) {
			string path = "assets/audio/" + chunks[i] + ".wav";
			music->chunkList[i] = Mix_LoadWAV(path.c_str());
		}
	}
}

void Game::update() {
	SDL_GetMouseState(&mouseX, &mouseY); //update mouse position
	//cout << "X: " << mouseX << "  " << "Y: " << mouseY << endl;
	//cout << countdown->getTimeLeft() << endl;
	if (playerCharacter != DEFAULT) {
		SDL_ShowCursor(0); // hide default os's cursor
	}
	else {
		SDL_ShowCursor(1); //return to default os's cursor
	}
	//draw cursor on screen
	switch (playerCharacter) {
	case HARRY:
	case DUMBLEDORE:
	case VOLDEMORT:
		if (cursorTx != NULL) {
			cursorRect.x = mouseX;
			cursorRect.y = mouseY;
			cursorRect.w = cursorRect.h = 32; //idk if it's too small ...
		}
		break;
	case DEFAULT:
		break;
	default:
		break;
	}

	switch (gameState) {
	case Intro:
		intro->update();
		break;
	case Ingame:
		tile->update();
		if (countdown->getTimeLeft() == 0) {
			gameState = End;
		}
		break;
	case End:
		//cout << countdown->getTimeLeft() << endl;
		endScreen->update();
		break;
	case Option:
		optionMenu->update();
		break;
	default:
		break;
	}


	//tile->update();
	
}

void Game::handleEvents() {
	SDL_Event e;
	SDL_PollEvent(&e);
	//check one per time
	switch (e.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mouseX, &mouseY);
		if (gameState == Intro) {
			if (intro->button[START]->bFocus == true) {
				gameState = Ingame;
				//countdown->reset();
				tile = new Tile();
				tile->preLoad(c);
				countdown->reset();
				return;  // so !(tile->check(mouseX, mouseY)) wont run;
			}
			else if (intro->button[EXIT]->bFocus == true) {
				isRunning = false;
			}
			else if (intro->button[OPTION]->bFocus == true) {
				gameState = Option;
				return;
				//optionMenu = new OptionMenu();
			}
		}
		if (gameState == Ingame) {
			if (countdown->isPaused == false && !(tile->check(mouseX, mouseY))) {
				//isRunning = false;
				gameState = End;
				//endState = true;
				//if (tile->score >= tile->hScore) 
				endScreen = new EndScreen(tile->score, tile->hScore, "YOU TAPPED A WHITE TILE!!!");
				return;
			}
			if (pause->bFocus == true) {
				if (countdown->isPaused == false) {
					countdown->pause();
					//countdown->isPaused == true;
				}
				else {
					//countdown->isPaused == false;
					countdown->resume();
				}
			}
		}
		if (gameState == End) {
			//if (endScreen == NULL) endScreen = new EndScreen(tile->score);
			if (endScreen->button[QUIT]->bFocus == true) isRunning = false;
			else if (endScreen->button[RESTART]->bFocus == true) {
				tile->~Tile();
				tile = NULL;
				tile = new Tile();
				tile->preLoad(c);
				endScreen->~EndScreen();
				endScreen = NULL;
				countdown->reset();
				gameState = Ingame;
				return;
			}
		}
		if (gameState == Option) {
			if (optionMenu->backToMenu->bFocus == true) {
				gameState = Intro;
				return;
			}
			else {
				for (int i = 0; i < 3; i++) {
					if (optionMenu->character[i]->bFocus == true) {
						playerCharacter = i; //see (enum) Character for more detail
						cursorTx = Texture::loadTexture(optionMenu->characterTxPath[i].c_str());
						gameState = Intro;
						return;
					}
				}
			}

		}
		break;
	default:
		break;
	}

}

void Game::clean() {
	if (music != NULL) music->~Music();
	if (tile != NULL) tile->~Tile();
	if (countdown != NULL) countdown->~Timer();
	if (intro != NULL) intro->~StartScreen();
	if (endScreen != NULL) endScreen->~EndScreen();
	if (pause != NULL) pause->~Button();
	if (optionMenu != NULL) optionMenu->~OptionMenu();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	cout << "Quit!" << endl;
	SDL_Quit();
}

void Game::render() {
	//clear previous renderer if existed
	SDL_RenderClear(renderer);
	//SDL_RenderCopy(renderer, background, NULL, NULL);
	//SDL_RenderCopy(renderer, image, NULL, &dst);

	switch (gameState) {
	case Intro:
		intro->render();
		break;
	case Ingame:
		tile->render();
		break;
	case End:
		if (endScreen == NULL) endScreen = new EndScreen(tile->score,tile->hScore, "OUT OF TIME!!!");
		endScreen->render();
		break;
	case Option:
		optionMenu->render();
		break;
	default:
		break;
	}
	//tile->render();
	if (cursorTx != NULL) {
		SDL_RenderCopy(renderer, cursorTx, NULL, &cursorRect);
	}
	SDL_RenderPresent(renderer);
}

bool Game::running() {
	return isRunning;
}
