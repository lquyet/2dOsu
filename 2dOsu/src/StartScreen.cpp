#include "../include/StartScreen.h"

extern Game* game;


StartScreen::StartScreen() {
	startScreenBackground = Texture::loadTexture("assets/IntroImage.png");

	button[START] = new Button("assets/button_start.png", 0, 500);
	if (button[START] == NULL) cout << 1 << endl;
	button[START]->focusButton = Texture::loadTexture("assets/button_start_focus.png");
	button[START]->center(WIDTH / 2);

	button[OPTION] = new Button("assets/button_option.png", 0, 560);
	button[OPTION]->focusButton = Texture::loadTexture("assets/button_option_focus.png");
	button[OPTION]->center(WIDTH / 2);

	button[EXIT] = new Button("assets/button_exit.png", 0, 620);
	button[EXIT]->focusButton = Texture::loadTexture("assets/button_exit_focus.png");
	button[EXIT]->center(WIDTH / 2);
}

StartScreen::~StartScreen() {
	button[START]->~Button();
	button[OPTION]->~Button();
	button[EXIT]->~Button();
	SDL_DestroyTexture(startScreenBackground);
}

void StartScreen::update() {
	button[START]->update();
	button[OPTION]->update();
	button[EXIT]->update();
}

void StartScreen::render() {
	SDL_RenderCopy(Game::renderer, startScreenBackground, NULL, NULL);
	button[START]->render();
	button[OPTION]->render();
	button[EXIT]->render();
	
}

//End Screen 

EndScreen::EndScreen(int score,int hiScore, std::string msg) {
	TTF_Font* font80 = TTF_OpenFont("font/Bariol.ttf", 80);
	TTF_Font* font120 = TTF_OpenFont("font/Bariol.ttf", 100);
	SDL_Color color1 = { 255, 155, 23 };
	SDL_Color color2 = { 221, 97, 74 };
	tScore = new Textbox("Your Score: " + to_string(score), font80, color1, 0, 0);
	tScore->center(WIDTH / 2, HEIGHT / 2);
	highestScore = new Textbox("Highest Score: " + to_string(hiScore), font80, color1, tScore->dst.x, tScore->dst.y + 80);
	//highestScore->center(WIDTH / 2, HEIGHT / 2 + 80);
	TTF_CloseFont(font80);
	//endScreenBackground = Texture::loadTexture("assets/backgroundBlack.png");
	SDL_SetRenderDrawColor(Game::renderer, 189, 209, 197, 255);
	button[RESTART] = new Button("assets/button_restart.png", 0, 570);
	button[RESTART]->focusButton = Texture::loadTexture("assets/button_restart_focus.png");
	button[RESTART]->center(WIDTH / 2);
	button[QUIT] = new Button("assets/button_quit.png", 0, 650);
	button[QUIT]->focusButton = Texture::loadTexture("assets/button_quit_focus.png");
	button[QUIT]->center(WIDTH / 2);
	failMsg = new Textbox(msg,font120, color2, 0, 200);
	TTF_CloseFont(font120);
	failMsg->center(WIDTH / 2);
}

EndScreen::~EndScreen() {
	button[RESTART]->~Button();
	button[QUIT]->~Button();
	tScore->~Textbox();
	failMsg->~Textbox();
	highestScore->~Textbox();
	//SDL_DestroyTexture(endScreenBackground);
}

void EndScreen::update() {
	button[RESTART]->update();
	button[QUIT]->update();
	//no need to update textbox (static textbox)
}

void EndScreen::render() {
	//SDL_RenderCopy(Game::renderer, endScreenBackground, NULL, NULL);
	tScore->render();
	highestScore->render();
	failMsg->render();
	button[RESTART]->render();
	button[QUIT]->render();
}