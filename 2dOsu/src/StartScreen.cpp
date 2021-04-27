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

EndScreen::EndScreen(int score) {
	TTF_Font* font = TTF_OpenFont("font/Bariol.ttf", 80);
	SDL_Color color1 = { 28,135,179 };
	SDL_Color color2 = { 0,0,0 };
	tScore = new Textbox(to_string(score), font, color1, 0, 0);
	TTF_CloseFont(font);
	tScore->center(WIDTH / 2, HEIGHT / 2);
	endScreenBackground = Texture::loadTexture("assets/backgroundBlack.png");
	button[RESTART] = new Button("assets/button_restart.png", 0, 0);
	button[RESTART]->focusButton = Texture::loadTexture("assets/button_restart_focus.png");
	button[RESTART]->center(WIDTH / 2);
	button[QUIT] = new Button("assets/button_exit.png", 0, 0);
	button[QUIT]->focusButton = Texture::loadTexture("assets/button_exit_focus.png");
	button[QUIT]->center(WIDTH / 2);
}

EndScreen::~EndScreen() {
	button[RESTART]->~Button();
	button[QUIT]->~Button();
	tScore->~Textbox();
	SDL_DestroyTexture(endScreenBackground);
}

void EndScreen::update() {
	button[RESTART]->update();
	button[QUIT]->update();
	//no need to update textbox (static textbox)
}

void EndScreen::render() {
	SDL_RenderCopy(Game::renderer, endScreenBackground, NULL, NULL);
	tScore->render();
	button[RESTART]->render();
	button[QUIT]->render();
}