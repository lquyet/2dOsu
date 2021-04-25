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